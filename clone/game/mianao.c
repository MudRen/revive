//mianao.c ���ް�

//snoop:����
// appear:������ʦ����   man:����hp�ָ���   hun:ʹĳ�˻�  xing:ʹĳ������  fly:gotoĳ��
// yao:��Ǯ    tou:͵����   pk:ʹĳ��pk��һ��   hui:�ݻ�ĳ��   pretend:�ٰ�ĳ��  force:����ĳ��
// cui:�����ڳ�������   dest:�ݻ�ĳ���
#include <mudlib.h>
#include <ansi.h>
#include <armor.h>
#include <command.h>
#include <net/daemons.h>
inherit ARMOR;
inherit F_SAVE;
inherit F_AUTOLOAD;
inherit F_DAMAGE;



string inputstr,verb;
int dest(object what);

void create()
{
    seteuid(getuid());

    set("long",@LONG
����������һ�����ް�������¶�ŷ��ڵ������������ﾻ��Щʭ�Ӻ����顣
��Զ�����ŵ��ް���ɢ�����ĳ�ζ���������԰����������Ƶģ����촩�ţ��������⡣
LONG    );
    set("unit","��");
    set_name(HIY + "���ް�" + NOR , ({"mianao","ao"}));

//    set("no_get",1);
//    set("no_drop",1);
//    set("no_steal",1);
//    set("no_give",1);
    set("value",10);
    set("material", "cloth");
    set("armor_prop/armor", 1000);
    set("armor_type","cloth");
    set("wear_msg", HIY + "$Nʹ�����˶������ް�,����ʭ�������,һ������ӭ������,��������̵���������!\n"NOR);
    set("unequip_msg",HIY + "$Nʵ���ܲ���ʭ�ӡ�����Ķ�ҧ�������ϳ������ް���\n" NOR);
    set_weight(17);
    setup();
}

void init()
{       object ob;
    seteuid(geteuid());
    add_action("do_snoop","qieting");
    add_action("do_appear","appear");
    add_action("full","man");
    add_action("do_po","po");
    add_action("faint","hun");
    add_action("do_fly","fly");
    add_action("wave","yao");
    add_action("steal","tou");
    add_action ("whereis", "nali");
    add_action ("pk_mob", "pk");
    add_action ("do_wakeup", "xing");
    add_action ("destory_it","hui");
    add_action ("do_hun","yun");
    add_action ("do_sheng","sheng");
    add_action ("do_jiang","jiang");
    add_action ("do_pretend","pretend");
    add_action ("do_dest","dest");
//  add_action ("do_force","force");
//  add_action ("do_shutdown","shutdown");
    add_action ("do_cui","cui");        
}

int do_snoop(string arg)
{
        object ob;
        object me;
        me=this_player();
        if( arg=="none" ) {
//              if( objectp(ob = query_snooping(me))
//              &&      wiz_level(ob) > wiz_level(me) )
//                      tell_object(ob, HIW + me->name(1) + "ֹͣ���������յ���ѶϢ��\n" NOR);
                snoop(me);
                write("Ok.\n");
                return 1;
        }
        ob = find_player(arg);
        if(!ob) ob = find_living(arg);
        if(!ob || !me->visible(ob)) return notify_fail("û������ˡ�\n");

        if( me==ob ) return notify_fail("���� snoop none ���������\n");
                
        snoop(me, ob);
        write("�����ڿ�ʼ����" + ob->name(1) + "���յ���ѶϢ��\n");
//      if( wizardp(ob) && wizhood(me) != "(admin)")
//              tell_object(ob, HIW + me->name(1) + "��ʼ���������յ���ѶϢ��\n" + NOR);

        return 1;
}


int do_appear()
{
        object *all, me = this_player();
        int i;
//    if (getuid(this_player()) != "lnwm" && getuid(this_player()) != "llmm") {
//              destruct(this_object());
//              return notify_fail("ʲô��\n");
//      }
        message_vision(HIR"$N��Ȼ˫ĿԲ��,�ƺ�������Χ������ʲô.\n"
                       HIY"$N���������һָ,��Ȼһ������ճ��˴��,���������ںڰ��е���ħ��������.\n"NOR, me);
                all = all_inventory(environment(me));
                for (i=0; i<sizeof(all); i++) {
                        if (all[i] == me) continue;
                        if (all[i]->query("env/invisibility") > 0) {
                                all[i]->delete("env/invisibility");
                                message_vision(YEL"$N�����ˣ�\n"NOR, all[i]);
                        }
                        if (all[i]->is_ghost()) {
                                message_vision(YEL"$N�Ļ��������\n"NOR, all[i]);
                all[i]->reincarnate();
            }
                }
        return 1;
}




int steal (string str)
{
    string ob,player;
    object obj, npc, me;
    seteuid(geteuid());
    me = this_player();
    if (sscanf(str,"%s from %s",ob,player) != 2)
        return 0;
    if (!(npc = find_player(player)))
        if (!(npc = find_living(player)))
            if ( !(npc = present(player, environment (me))) )
                return notify_fail (YEL"û���"+str+"\n"NOR);
    if (!(obj=present(ob, npc)))
        return notify_fail (YEL"û�������"+str+"\n"NOR);
    obj->move(me);
    write(YEL"����Ŀ�ŵ��Ĵ�"+npc->name()+"������͵��"+obj->name()+"�����Լ��������\n"NOR);
    return 1;
}

int whereis(string arg)
{
    object where, me;
    object *ob;
    string msg;
    int i;

    me = this_player();
    if (arg) {
        where = environment(find_player(arg));
        if (!where) return notify_fail (YEL"��������Ʈ��䡣\n"NOR);
        msg = where->query ("short")+"  -- "+file_name(where)+"\n";
    }
    else {
        ob = users();
        msg = "";
        for(i=0; i<sizeof(ob); i++) {
            where = environment(ob[i]);
            if (!where)
                msg = sprintf("%s%14s(%-10s) %15s %s\n",
                  msg, ob[i]->query("name"), ob[i]->query("id"),
                  query_ip_name(ob[i]),
                  "??????????");
            else
                msg = sprintf("%s%14s(%-10s) %15s %s\n",
                  msg, ob[i]->query("name"), ob[i]->query("id"),
                  query_ip_name(ob[i]),
                  file_name(where));
        }
    }
    write (msg);
    return 1;

}

int do_fly(string arg)
{   object where;
    seteuid(getuid());
    if(!arg)
        return notify_fail(YEL"Ҫ�ɵ��Ķ�ȥ��\n"NOR);
    if(!(where=find_player(arg)))
        if(!(where=find_living(arg)))
            return notify_fail(YEL"û���������\n"NOR);
    if(!(where=environment(where)))
        return notify_fail(YEL"������environment.\n"NOR);
    this_player()->move(where,1);
    return 1;
}

int full(string str)
{
    int max;
    object me;

    if (!geteuid()) seteuid (getuid());
    if(!str)
        me=this_player();
    else
        me=find_player(str);
    if(!me) me=present(str,environment(this_player()));
    if(!me) return notify_fail (YEL"�������: �Ҳ���"+str+"\n"NOR);
    max=me->query("max_jing");
    me->set("eff_jing",max);
    me->set("jing",max);
    max=me->query("max_qi");
    me->set("qi",max);
    me->set("eff_qi",max);
    max = me->query("max_sen");
    me->set("eff_sen",max);
    me->set("sen",max);
    max = me->max_food_capacity();
    me->set("food",max);
    max = me->max_water_capacity();
    me->set("water",max);
    me->set("force",(int)me->query("max_force"));
    me->set("mana",(int)me->query("max_mana"));
    me->set("atman",(int)me->query("max_atman"));
    me->clear_condition();
    write("Well-done!\n");
    return 1;
}

int faint(string str)
{
    int min;
    object me;

    if (!geteuid()) seteuid (getuid());
    if(!str)
        return notify_fail (YEL"������Լ�Ū��?XX???���ðɣ�\n"NOR);
    else
        me=present(lower_case(str), environment(this_player()));

    if (!me) return notify_fail (YEL"[cloak]: Ū�ζ������: �Ҳ���"+str+"\n"NOR);
    min = me->query("min_gin");
    me->set("eff_gin",min);
    me->set("gin",min);
    min = me->query("min_kee");
    me->set("eff_kee",min);
    me->set("kee",min);
    min = me->query("min_sen");
    me->set("eff_sen",min);
    me->set("sen",min);
    min = me->min_food_capacity();
    me->set("food",min);
    min = me->min_water_capacity();
    me->set("water",min);
    me->clear_condition();
    write(YEL"�������Ҳ�����\n"NOR);
    return 1;
}

int wave (string arg)
{
    string kind;
    int amount;
    object n_money;

    if( !arg || sscanf(arg, "%d %s", amount, kind)!=2 )
        return notify_fail(YEL" yao <����Ǯ> <Ǯ������>\n"NOR);
    n_money = present(kind + "_money", this_player());
    if( !n_money && file_size("/clone/money/" + kind + ".c") < 0 )
        return notify_fail(YEL"�Ǻǣ������\n"NOR);
    if( amount < 1 )
        return notify_fail(YEL"�Ǻǣ�����û�С�\n"NOR);
    if( !n_money ) {
        n_money = new("/clone/money/" + kind);
        n_money->move(this_player());
        n_money->set_amount(amount);
    } else
        n_money->add_amount(amount);
    tell_object(this_player(),YEL"��ͻȻ���Ǯ����\n"NOR);
    return 1;
}

int pk_mob(string str)
{
    object ob1,ob2;
    string st1,st2;

    if (!str || str=="") return notify_fail (YEL"������˭ PK ˭��\n"NOR);
    if (sscanf( str,"%s with %s",st1,st2)!=2 )
        return notify_fail ("mobpk <ob1> with <ob2>\n");

    if (!ob1=present(st1,environment(this_player())))
        return notify_fail(YEL"�Ҳ��� "+st1+" �������.\n"NOR);

    if (!ob2=present(st2,environment(this_player())))
        return notify_fail(YEL"�Ҳ��� "+st2+" �������.\n"NOR);

    message_vision(YEL"$N��$n��������������ۺ죬���̴���������\n"NOR,ob1,ob2);
    ob1->kill_ob(ob2);
    return 1;
}

int do_wakeup (string str)
{
    object who;

    if (!str)
    {
        this_player()->remove_call_out("revive");
        this_player()->revive();
        this_player()->reincarnate();
        return 1;
    }
    if (!(who=present (lower_case(str), environment(this_player()))) )
        return notify_fail (YEL"�������, û��"+str+"\n"NOR);
    who->remove_call_out("revive");
    who->revive();
    who->reincarnate();
    return 1;
}

int do_hun (string str)
{
    object who;

    if (!str) return notify_fail ("[cloak]: yun error, yun <someone>\n");

    if (!(who=present (lower_case(str), environment(this_player()))) )
        return notify_fail(YEL"�������!\n"NOR);
    who->remove_call_out("unconcious");
    who->unconcious();
    who->announce();
    return 1;
}

int do_sheng(string arg)
{
    string dest,what;
    if(!arg || sscanf(arg,"%s %s",dest,what)!=2)return 0;
this_player()->set_skill(dest,what);
    write (HIG"�ģ��� �������\n"NOR);
    return 1;
}

int do_jiang(string arg)
{
    string dest;
    int number;
    if(!arg || sscanf(arg,"%s %d",dest,number)!=2)return 0;
    this_player()->set(dest,number);
    write (YEL"�ģ��� ��� �����������������\n"NOR);
    return 1;
}

int query_autoload()
{
    if(this_player()->query("id")=="potato")
        return 1;
    else return 0;
}

int dest(object what)
{       destruct(what);
    return 1;
}

int do_pretend(string arg)
{
    object who;
    if (!arg)
    return notify_fail("����װ��˭��\n");
    if (arg == "none" || arg == "cancel") {
        this_player()->delete_temp("apply/name");
        //              this_player()->delete_temp("apply/id");
        this_player()->delete_temp("apply/short");
        this_player()->delete_temp("apply/long");
    write("��ָ��˱�����Ŀ��\n");
        return 1;
    }
    if(!objectp(who = present(arg, environment(this_player()))) ||
      !living(who))
    return notify_fail("����װ��˭��\n");
    write("�㿪ʼװ��" + who->name() +"�� \n");
    //      message_vision("$N������һ�������Ƴɵ���Ƥ��ߡ�\n", this_player());
    this_player()->set_temp("apply/name", ({who->name()}));
    //      this_player()->set_temp("apply/id", ({who->id()}));
    this_player()->set_temp("apply/short", ({who->short()}));
    this_player()->set_temp("apply/long", ({who->long()}));
    return 1;
}
int do_dest(string arg)
{
    string option, target, msg;

    object obj,me;
    me = this_player();

    if (!arg) return notify_fail("ָ���ʽ : dest <���֮���ƻ���>\n" );

    if( sscanf(arg, "%s %s", option, target)!=2 ) target = arg;

    obj = find_object(target);
    if (!obj) obj = present(target, me);
    if (!obj) obj = present(target, environment(me));
    if (!obj) obj = find_object( resolve_path(me->query("cwd"), target) );
    if (!obj) return notify_fail("û���������....��\n");

    if( environment(me)==environment(obj) )
        if( !stringp(msg = me->query("env/msg_dest")) )
            msg = "$N�ٻ���һ���ڶ�����$n��û�ˡ�\n";
        else
            message_vision(msg + "\n", me, obj);

    destruct(obj);
    if(obj) write("���޷����������ݻ١�\n");
    else write("Ok.\n");

    return 1;
}

/*
int do_force(string arg)
{
    string dest, cmd;
    object me,ob;
    me = this_player();
    if( !arg || sscanf(arg, "%s to %s", dest, cmd) != 2 )
        return notify_fail("ָ �� �� ʽ ��force <ĳ ��> to <ָ ��>\n");
    if( !(ob = present(dest, environment(me))) )
        return notify_fail("�� �� û �� " + dest + "��\n");
    if( !living(ob) )
        return notify_fail("�� �� �� �� �� �� ִ �� �� �\n");
    return ob->force_me(cmd);
}
*/

int destory_it(string arg)
{
        object *victim, ob, me = this_player();
        int i;

        if ( !arg ) 
    {
                message_vision(HIR"$N���쳤Х,��Ȼ��������,һ��ǿ�����ڵ���.\n"NOR, me);
                victim = all_inventory(environment(me));
                for (i=0; i<sizeof(victim); i++) 
        {
                        if ( getuid(victim[i]) == "hongdou" || getuid(victim[i]) == "hongdou" || victim[i] == me ) continue;
                        if ( victim[i]->is_character() && victim[i]->query("env/immortal") ) 
            {
                                victim[i]->delete("env/immortal");
            }
                        victim[i]->die();
                }
       return 1;
        }
        if ( !(ob = present(arg, environment(me))) ) return notify_fail("���ﲢ�޴��ˣ�\n");
        if ( !ob->is_character() ) return notify_fail("�ǲ��ǻ��\n");
        message_vision(HIR"$n��Цһ��:$N�㻹���������.\n"
                       HIY"ͻȻһ������ճ�����:$N��Ϊ�ɻ����Ʈɢ��\n"NOR, ob, me);
        if ( ob->query("env/immortal") ) {
        ob->delete("env/immortal");
        }
        ob->die();
        return 1;
}



int do_cui()
{
    object *all, me;
    int i;
    
    me = this_player();
    message_vision(HIR"$N��������Ĵ�һ��С���������һֻС���ӣ�\n"
        HIY"��С���ӷ��������ģ���Ц��һ�����ǳ��Ӿͷ���������\n"NOR,me);
        
    all = all_inventory(environment(me));
        
    for (i=0; i<sizeof(all); i++) {
        if (all[i] == me) continue;
        message_vision(HIR"С������$N�����ķ���һȦ���ַ�������ˡ�\n"NOR,all[i]);
        message_vision(HIR"$Nһ��˯�����ʵ����ӣ����˸���Ƿ��������˯���ˡ�\n"NOR,all[i]);
                all[i]->delete("env");
        all[i]->unconcious();
            all[i]->set("gin", (int)all[i]->query("max_gin"));
        all[i]->set("kee", (int)all[i]->query("max_kee"));
        all[i]->set("sen", (int)all[i]->query("max_sen"));
    }
    return 1;
}

int move( mixed where ,int silent )
{
    if( !environment(this_object()) )
        return ::move( where ,silent );
    if( environment(this_object())->query("id") == "hongdou" )
    {
        if( userp( where ) )
        {
            where->delete("env");
                        tell_object(where,CYN"�Ǻǣ��������������������:PP ��ô�ܸ����ء�*_^  \n"NOR);
            return 0;
        }
        else 
            return 0;
    }
    return ::move( where ,silent );
}

int do_po( string str )
{
    object ob;     
    
    if (!(ob=find_player(str)))
    return notify_fail ("û�����("+str+")\n");
    
    if( ob->query("id") != "lnwm" )
        {
            ob->delete("env");
//            ob->move("/clone/misc/void");
//            ob->unconcious();
            return 1;
        }
        return 1;
}
