// cuised.c ���ξ���

#include <ansi.h>
#include <mudlib.h>

#pragma optimize
#pragma save_binary

// ���ξ�����ι�����
// ÿ��վ������ξ��鸺�������֤�����ݴ��䡣�����Ժ�����
// ��������һ���˿ڣ���ѯ��������վ�������
//
// �������Σ�
// ���ĳ��վ���½������վ�����ι�����ʹ���ߣ���վ���ԭ
// ʼվ�����ξ��������ø���ҵ����ݣ����� login & user ��
// ���֡�Ȼ�������Щ�����ڱ�վ�㹹��һ����ң�������Щ����
// �������ڱ�վ��������˳���ʱ�򴫵ݻ�ԭ�ȵ�վ�㡣��ʦʹ��
// ���ַ�ʽ�������Ρ�
//
// ��֤���̣�
// ���ξ�������������߾����������֤���󣬲�������Ҫ�����
// վ�������ݡ�������������Ҫ�����û����Ϳ��� -- �������
// ͨ��һ���ֶν��б��ܡ����������Ժ󽫲����Ƿ���ȷ��������
// Ӧ����Ϣ�����յ����ص���ȷ��Ϣ�Ժ����ξ���������������
// �߾��顣
//

// �����Ķ˿�(��MUD�������˿�Ϊ��׼)
#define CRUISE_PORT                     13

// ͬʱ����֤���������
#define MAX_AUTHENTICATING_USER         32

// ��֤�ȴ����ʱ��(��)
#define MAX_AUTHENTICATING_TIME         180

// �ڲ�����
static int cfd;
mixed auth_info = ({ });

// �ṩ���ⲿ�Ľӿ�
void authenticate_user(object ob, string passwd);

private void server_init();
private void in_listen_callback(int fd);
private void in_read_callback(int fd, string str);
private void in_write_callback(int fd);
private void in_close_callback(int fd);

void create() 
{
	seteuid(ROOT_UID);
	set("channel_id", "���ξ���");

        call_out("server_init", 0);
}

// �ṩ�汾����
private void server_init()
{
        int port;

        CAHNNEL_D->do_channel(this_object(), "sys", "���ξ���������");

        // ��������ͨѶ��SOCKET
        cfd = socket_create(STREAM_BINARY,
                            "in_read_callback",
                            "in_close_callback" );

	if (cfd < 0)
        {
                log_file("cruise", sprintf("%s Failed to create socket.\n", log_time()));
		return;
	}

        // Ȼ���SOCKET
        port = get_config(__MUD_PORT__) + CRUISE_PORT;
	if (socket_bind(cfd, port) < 0)
        {
		log_file("cruise", sprintf("%s Failed to bind socket.\n", log_time()));
		socket_close(cfd);
		return;
	}

        // ������
	if (socket_listen(vfd, "in_listen_callback" ) < 0)
        {
		log_file("cruise", sprintf("%s Failed to listen to socket.\n", log_time()));
		return;
	}

        // ��ʼ��������Ϣ
        socket_info = ([ ]);
}

// �汾����վ������������վ�������
private void in_listen_callback(int fd)
{
	int new_fd;
        string address;
        string ip;
        int port;

	if ((new_fd = socket_accept(fd, "in_read_callback",
                                        "in_write_callback")) < 0)
                // û�гɹ��Ľ��������������
		return;

        address = socket_address(new_fd);
        if (! stringp(address) || sscanf(address, "%s %d", ip, port) != 2 ||
            ! CONFIG_D->query(ip))
        {
                // �����ַû�о�����Ȩ
                socket_close(new_fd);
                return;
        }

        sys_info(sprintf("վ�� %s ���Ӱ汾��ʼͬ���汾��", ip));

        socket_info[new_fd] = allocate(7);
	socket_info[new_fd][STATUS] = STATUS_LOGIN;
        socket_info[new_fd][CMD_BUFFER] = "";
        socket_info[new_fd][CMD_QUEUE] = ({ });
        socket_info[new_fd][PENDING_WRITE] = ({ });

        // ����״̬
        socket_info[new_fd][STATUS] = STATUS_WAIT_COMMAND;
	in_write_callback(new_fd);
}

// ������Ϣ
private void in_read_callback(int fd, mixed mess)
{
        int cc;
	string *cmds;
        mixed  prefix;
        string str;

	if (! arrayp(socket_info[fd]))
                return;

        if (stringp(mess))
                // ���յ����ַ���
                str = mess;
        else
        if (bufferp(mess))
                // ���յ��˻�����
                str = read_buffer(mess, 0, sizeof(mess));
        else
                return;

        if (! str) return;

	str = replace_string( str, "\r", "");
        if (stringp(prefix = socket_info[fd][CMD_BUFFER]))
                str = (string) prefix + str + "\n";
        else
                str += "\n";

	cmds = explode(str, "\n");
        socket_info[fd][CMD_BUFFER] = cmds[sizeof(cmds) - 1];

        if (sizeof(cmds) > 1)
        {
                // ����Щ������뵽���������
                cc = sizeof(socket_info[fd][CMD_QUEUE]);
                socket_info[fd][CMD_QUEUE] += cmds[0..<2];
                if (socket_info[fd][STATUS] == STATUS_WAIT_COMMAND)
                        // ���ڽ�������״̬
                        parse_cmd(fd);
        }
}

// �ɹ�д��
private void in_write_callback(int fd)
{
        buffer buf;
        int pos, len;
        int i;

        for (i = 0; i < 32; i++)
        {
                // ѭ��������Ϣ
                reset_eval_cost();

                // �Ѿ��������ˣ�
        	if (! arrayp(socket_info[fd]))
                        // �ǣ��������Ҫ����������
                        return;

                // �������������ͨ��Ϣ�����ҷ��ͳ�ȥ
                while (sizeof(socket_info[fd][PENDING_WRITE]))
                {
                        // ����������Ϣ������֮
                        if (send_pending_msg(fd) != 0)
                                // û�гɹ��ķ��ͣ��ȴ���һ�η���
                                return;
                }

                // ���ݵ�ǰ��״̬���н�һ������
                switch (socket_info[fd][STATUS])
                {
                case STATUS_SENDING:
                        // ���ڷ����ļ�
                        pos = socket_info[fd][FILE_POS];
                        len = socket_info[fd][FILE_SIZE] - pos;
                        if (len > FILE_BLOCK)
                                len = FILE_BLOCK;
                        if (len > 0)
                        {
                                buf = read_buffer((string) socket_info[fd][FILE_NAME], pos, len);
                                if (sizeof(buf) != len)
                                        // ��ȡû����ȫ�ɹ�����д�㷢�͡�
                                        buf = allocate_buffer(len);
                                // �ж���β����Ľ��
                                switch (socket_write(fd, buf))
                                {
                                case EESUCCESS:
                                        // �ƶ��α�
                                        pos += len;
                                        break;

                                case EECALLBACK:
                                        // �ƶ��α�
                                        pos += len;

                                        // �ȴ�CALLBACK���Ȳ���������
                                        socket_info[fd][FILE_POS] = pos;
                                        return;

                                case EEWOULDBLOCK:
                                        // ����æ
                                        call_out("in_write_callback", 2, fd);
                                        return;

                                default:
                                        // ����ʧ�ܣ��ȴ��´�callback
                                        return;
                                }
                        }

                        // �ж��ļ��Ƿ������
                        if ((socket_info[fd][FILE_POS] = pos) >=
                            socket_info[fd][FILE_SIZE])
                        {
                                // �ļ��Ѿ�������ϣ�����״̬
                                socket_info[fd][STATUS] = STATUS_WAIT_COMMAND;
                                if (! sizeof(socket_info[fd][CMD_QUEUE]))
                                        // �Ѿ�û�д������������
                                        return;

                                // �����������ΪʲôҪ��
                                // this_object() ���к��У�
                                // ����ǲ���ʡ�Եģ���Ϊ��
                                // ���������ֵĺ����Ϳ��Ը�
                                // ��previous_object() �ֱ�
                                // �Ƿ���������callback�ڡ�
                                this_object()->parse_cmd(fd);

                                // ������ѭ�����ᴦ����������Ľ��
                        }

                        // ���ʹ������
                        break;
        
                default:
                        // δ����״̬���޲���
                        return;
                }

                // һ�δ���(switch)��ϣ�ѭ����������
        }

        // ����̫����
        debug_info("�� SOCKET д������̫�࣬�ݻ���");
        call_out("in_write_callback", 1, fd);
}

// ���ӶϿ�
private void in_close_callback(int fd)
{
        string address;

        address = socket_address(fd);
        if (stringp(address))
                sscanf(address, "%s %*d", address);
        else
                address = "unknow";

        sys_info(sprintf("վ�� %s �ͱ�վ�Ͽ������ӡ�", address));

        // �����Ϣ
        map_delete(socket_info, fd);
}

// �� LOGIN_D ���õĽӿ�
int authenticate_user(object ob, string passwd)
{
        string site;
        string id;
        object aob;
        mixed info;
        int i;

        if (! stringp(site = ob->query_temp("site")))
                return 0;

        if (! stringp(id = ob->query("id")))
                return 0;

        if (! interactive(ob))
                return 0;

        if (site == INTERMUD_MUD_NAME)
                return 0;

        for (i = 0; i < sizeof(auth_info); i++)
        {
                if (! objectp(aob = auth_info[i][USER_OB]))
                        continue;

                if (! interactive(aob))
                {
                        destruct(aob);
                        auth_info[i] = 0;
                        continue;
                }
                        
                if (info[USER_ID] != id)
                        continue;

                if (query_ip_number(aob) == query_ip_number(ob))
                {
                        tell_object(aob, "��֤��ֹ��\n");
                        destruct(aob);
                        auth_info[i] = 0;
                }
        }

        info = allocate(USER_MAGIC_NUMBER + 1);
        info[USER_ID] = id;
        info[USER_OB] = ob;
//      info[USER_PASSWD] = passwd;
        info[USER_SITES] = site;
        info[USER_MAGIC_NUMBER] = time();

        auth_info -= ({ 0 });
        auth_info += ({ info });
}
