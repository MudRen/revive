// questd.c 处理任务的守护进程
// 包括师门任务函数载体和系统注册任务(SYSREG_QUEST)

#include <ansi.h>
#include <quest.h>

#pragma optimize
#pragma save_binary

inherit F_DBASE;

// 定义提供给外部调用的接口函数
varargs public void   bonus(object who, mapping b, int flag);
public void   delay_bonus(object who, mapping b);
public mixed  accept_ask(object me, object who, string topic);
public void   set_information(object qob, string key, mixed info);
public mixed  query_information(object qob, string key);
public void   remove_information(object qob, string key);
public void   remove_all_information(object qob);
public string generate_information(object knower, object who, string topic);
public void   start_all_quest();

void create()
{
        seteuid(getuid());
        set("channel_id", "任务精灵");
        set_heart_beat(900);
        call_out("collect_all_quest_information", 1);
}

#define ONE_DAY                 (86400 / 365)
#define MAX_QUEST_LEVEL         3

private void special_bonus(object me, object who, mixed arg)
{
        string *ob_list = ({
                "/clone/gift/xiandan",
                "/clone/gift/shenliwan",
                "/clone/gift/unknowdan",
                "/clone/gift/xisuidan",
                "/d/item/obj/hantie",
                "/d/item/obj/wujins",
                "/d/item/obj/butian",
                "/d/item/obj/tiancs",
                "/clone/gift/jinkuai",
        });
        object ob;

        message_vision("$n对$N微微一笑，道：干得不赖，辛苦"
                       "了，正好我这里有点东西，你就拿去吧。\n",
                       who, me);

        if (stringp(arg))
                ob = new(arg);
        else
                ob = new(ob_list[random(sizeof(ob_list))]);
        ob->move(who, 1);
        tell_object(who, HIM "你获得了一" + ob->query("unit") + ob->name() +
                        HIM "。\n" NOR);
}

varargs public void bonus(object who, mapping b, int flag)
{
        int exp;                // 奖励的经验
        int pot;                // 奖励的潜能
        int mar;                // 奖励的实战体会
        int shen;               // 奖励的神
        int score;              // 奖励的江湖阅历
        int weiwang;            // 奖励的江湖威望
        int pot_limit;          // 潜能的界限
        int mar_limit;          // 实战体会的界限
        int percent;            // 奖励的有效百分比
        string msg;             // 奖励的描述信息

        // 获得奖励的百分比
        percent = b["percent"];
        if (percent < 1 || percent > 100)
                percent = 100;

        exp = b["exp"] * percent / 100;
        pot = b["pot"] * percent / 100;
        mar = b["mar"] * percent / 100;
        shen = b["shen"] * percent / 100;
        score = b["score"] * percent / 100;
        weiwang = b["weiwang"] * percent / 100;

        if (! flag)
        {
                pot_limit = who->query_potential_limit() - who->query("potential");
                if (pot > pot_limit) pot = pot_limit;
                if (pot < 1) pot = 0;

                mar_limit = who->query_experience_limit() - who->query("experience");
                if (mar > mar_limit) mar = mar_limit;
                if (mar < 1) mar = 0;
        } else
        {
                if (who->query_potential_limit() < who->query("potential"))
                        pot = 1 + random(2);

                if (who->query_experience_limit() < who->query("experience"))
                        mar = 1;
        }

        // 生成提示信息
        if (stringp(msg = b["prompt"]))
                msg = HIG + msg + HIG "，你获得了";
        else
                msg = HIG "通过这次锻炼，你获得了";

        if (exp > 0) msg += chinese_number(exp) + "点经验、";
        if (pot > 0) msg += chinese_number(pot) + "点潜能、";
        if (mar > 0) msg += chinese_number(mar) + "点实战体会、";
        if (shen > 0) msg += chinese_number(shen) + "点正神、";
        if (shen < 0) msg += chinese_number(-shen) + "点负神、";
        if (score > 0) msg += chinese_number(score) + "点江湖阅历、";
        if (weiwang > 0) msg += chinese_number(weiwang) + "点威望、";

        msg += "能力得到了提升。\n" NOR;
        tell_object(who, sort_msg(msg));

        // bonus
        who->add("combat_exp", exp);
        who->add("potential", pot);
        who->add("experience", mar);
        who->add("shen", shen);
        who->add("score", score);
        who->add("weiwang", weiwang);
}

// 延迟奖励：有时候给出奖励的时候应该是在某些事件发生以后，
// 但是在该事件发生时给与奖励更易于书写程序，所以奖励生成的
// 地方在事件正在发生的时候，但是要让玩家看起来是在事件发生
// 以后。比如杀人，人死亡的时候给与奖励是容易做的，但是我希
// 望玩家在看到NPC 的死亡信息以后才看到奖励的信息，这时候就
// 用delay_bonus了。
public void delay_bonus(object who, mapping b)
{
        who->start_call_out((: call_other, __FILE__,
                               "bonus", who, b :), 1);
}

public mixed accept_ask(object me, object who, string topic)
{
        string my_fam;

        my_fam = me->query("family/family_name");

        if (topic == "历练" || topic == "历炼" ||
            topic == "锻炼")
        {
                if (my_fam != who->query("family/family_name"))
                        return "你是谁？找我有什么事情么？";

                if (who->query("out_family"))
                        return "去吧！" + who->name(1) + "，好自为之！";

                if (who->query("combat_exp") < 50000)
                {
                        message_sort(CYN "$N" CYN "叹了一口气，看了看$n"
                                     CYN "道：“你的武功基础还不太好，还是再"
                                     "好好锻炼吧！”\n", me, who);
                        return 1;
                }

                if (who->query("score") < 100)
                {
                        message_sort(CYN "$N" CYN "摆摆手道：“你的江湖"
                                     "阅历太少，现在不可外出独自行走江湖。”\n",
                                     me, who);
                        return 1;
                }

                who->set("out_family", 1);
                if (me->is_good())
                {
                        message_sort(HIY "$N" HIY "对$n" HIY "欣慰的点了"
                                     "点头，道：“看来我们" + my_fam +
                                     "又出了一位人才啊！你记住了！我辈武"
                                     "人，切忌不可好勇争斗，要多做行侠仗"
                                     "义之事！”\n" NOR, me, who);
                } else
                if (me->is_bad())
                {
                        message_sort(HIR "$N" HIR "对$n" HIR "哈哈大笑道"
                                     "：“好！好！你可以出去走走看看了，"
                                     "对那些自认所谓大侠之辈可不要手软，"
                                     "去吧！”\n" NOR, me, who);
                } else
                {
                        message_sort(HIY "$N" HIY "对$n" HIY "叮嘱道：“"
                                     "以后你行走江湖常常是孤身一人，记得"
                                     "要敬重前辈，不可狂妄自大，切记了，"
                                     "去吧！”\n" NOR, me, who);
                }

                message_sort("$N翻出一本小册子来，对$n道：“今后你行走江"
                             "湖，许多山川地理，世间风情你都可以记录在这"
                             "本地图册上，以咨参考，对你多少也会有些帮助"
                             "。”\n", me, who);

                tell_object(me, HIY"你获得了师傅赠给你的地图册，请参见帮"
                            "助(HELP QUEST)以\n获得更详细的信息。\n" NOR);

                CHANNEL_D->do_channel(this_object(), "rumor",
                        "听说" + who->name(1) + "已经开始闯荡江湖。");
                return 1;
        }
}

// 领取任务
// 如果目前正在协助别人，不能领取任务
int ask_quest(object me, object who)
{
        string fam;             // ME的门派信息
        object ob;              // 任务重的某些物件或人物
        mapping q;              // WHO的人物
        object aob;             // WHO目前正在协助的对象
        int exp;                // WHO的经验
        int t;                  // 用来计算时间的变量
        int level;              // QUEST的等级
        string place;

        message_vision("$n向$N打听有关任务的情况。\n", me, who);

        fam = me->query("family/family_name");
        if (who->query("family/family_name") != fam)
        {
                message_vision("$N瞪大眼睛看着$n，道：“你又不是我们" + fam +
                               "的，来捣什么乱？”\n", me, who);
                return 1;
        }

        q = who->query("quest");
        if (mapp(q))
        {
                if (q["master_id"] != me->query("id"))
                {
                        message_vision("$N看了看$n，哼了一声，没有理$n。\n",
                                       me, who);
                        return 1;
                }

                switch (q["type"])
                {
                case "kill":
                        message_vision("$N一脸怒容对$n道：“我不是让你" +
                                       CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前杀了" HIR + q["name"] + NOR "的吗？现在是" + 
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的人头呢？”\n", me, who);
                        break;
                case "letter":
                        message_vision("$N一脸怒容对$n道：“我不是让你" +
                                       CHINESE_D->chinese_monthday(q["limit"]) +
                                       "之前把信送到" HIC + q["name"] + NOR "那里的吗？现在是" + 
                                       CHINESE_D->chinese_monthday(time()) +
                                       "，他的回执呢？”\n", me, who);
                        break;
                }
                return 1;
        }

        if (me->query("eff_qi") * 2 < me->query("max_qi") ||
            me->query("qi") * 2 < me->query("max_qi"))
        {
                message_vision("$N捂着胸口，一副非常痛苦的样子，对你的"
                               "话显然没有听进去。\n", me);
                return 1;
        }

        exp = who->query("combat_exp");
        if (exp < 10000)
        {
                message_vision("$N叹了一口气，对$n道：“就你那点水平，"
                               "我实在没法给你派任务。”\n", me, who);
                return 1;
        }

        if (objectp(aob = who->query_temp("quest/assist")))
        {
                message_vision("$N看了看$n，道：“我听说你不是帮" +
                               aob->name(1) + "去了么？先办妥了"
                               "再说吧！”\n", me, who);
                return 1;
        }

        if (exp < 30000)
        {
                object letter;

                if (who->query("score") < 20)
                {
                        message_vision("$N摇摇头，对$n道：“可惜你的江湖阅历太差，"
                                       "不然我还可以让你帮我送封信。”\n", me, who);
                        return 1;
                }

                ob = new(CLASS_D("generate") + "/receiver.c");
                NPC_D->place_npc(ob, ({ "大理一带", "关外", "星宿海", "天山",
					"终南山", "西域" }));
                NPC_D->set_from_me(ob, me, 100);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                place = ob->query("place");

                letter = new("/clone/misc/letter");
                letter->set("long", "这是一封" + me->name() + "写给" + ob->name() +
                                    "的亲笔信函。\n");
                letter->set("send_from", me->query("id"));
                letter->set("send_to", ob->query("id"));
                letter->set("send_from_name", me->name());
                letter->move(me);
                message_vision("$N对$n道：“这封信你帮我交到" HIC + ob->name() +
                               NOR "手中，他现在应该在" + place +
                               "，然后把回执带回来给我！”\n", me, who);
                me->force_me("give letter to " + who->query("id"));
                who->set("quest/info", letter->query("id"));
                who->set("quest/type", "letter");
        } else
        if (exp < 50000)
        {
                message_vision("$N盯着$n看了半天，道：“让你送信委屈了你，"
                               "叫你闯荡江湖我又不放心，你还是好好练练功夫"
                               "吧！”\n", me, who);
                return 1;
        } else
        {
                if (! who->query("out_family"))
                {
                        message_sort("$N摆摆手，对$n道：“我现在这里倒是"
                                     "有一些事情，不过待你外出历练一段时"
                                     "间以后再说吧！”\n", me, who);
                        return 1;
                }

                if (who->query("score") < 2000)
                {
                        message_sort("$N叹了一口气，对$n道：“你还是在江"
                                     "湖上多历练历练，增进一些阅历再说吧"
                                     "！现在我对你还不够放心！”\n", me, who);
                        return 1;
                }

                if (who->query("weiwang") < 20)
                {
                        message_sort("$N看了看$n，叹气道：“你在江湖上一"
                                     "点名头都没有，我没法放心把任务交给"
                                     "你。”\n", me, who);
                        tell_object(me, "看来还是的加强自己的江湖威望才行。\n");
                        return 1;
                }
        
                if (who->is_bad() && me->is_good())
                {
                        message_sort("$N大怒道：“岂有此理！你居然已经误"
                                     "入歧途，还敢来见我！”\n", me, who);
                        return 1;
                }
        
                if (who->is_good() && me->is_bad())
                {
                        message_sort("$N大怒道：“岂有此理！几天不见，你"
                                     "居然也学起假仁假义来了，快给我滚！"
                                     "”\n", me, who);
                        return 1;
                }

                level = who->query_temp("quest/next_level");
                if (level < 0 || level > MAX_QUEST_LEVEL)
                        level = 0;

                ob = new(CLASS_D("generate") + "/killed.c");
                NPC_D->place_npc(ob, who->query("combat_exp") < 500000  ? ({ "大理一带", "终南山", "关外", "西域" }) :
                                     who->query("combat_exp") < 800000 ? ({ "大理一带", "终南山", "西域" }) : 0);
                NPC_D->set_from_me(ob, who, 100);
                ob->add_temp("apply/attack", ob->query_skill("force") *
					     (level - 1) / 15);
                ob->add_temp("apply/dodge", ob->query_skill("force") *
					    (level - 1) / 15);
                ob->add_temp("apply/parry", ob->query_skill("force") *
					    (level - 1) / 15);
                ob->add_temp("apply/damage", 5 + level * 7);
                ob->add_temp("apply/unarmed_damage", 5 + level * 7);
                ob->add_temp("apply/armor", 10 + level * 15);
                ob->set_temp("quester", who->query("id"));
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                NPC_D->random_move(ob);
                place = ob->query("place");

                message("vision", me->name() + "小声的对" + who->name() +
                        "吩咐着什么，" + who->name() +
                        "一边听，一边不住的点头。\n",
                        environment(who), ({ who }));
                if (me->is_good())
                {
                        ob->set("shen", -ob->query("combat_exp") / 2000);
			if (me->query("family/family_name") == "少林派")
				tell_object(who, me->name() + "对你道：“虽然我们出家人以" +
					"慈悲为怀，但是对于大凶大恶之徒也" +
					"不能放过，\n最近" + HIR + ob->name() +
					NOR "在" + place + "作恶"
				        "多端，你去把他除了，提头来见。”\n");
			else
                        	tell_object(who, me->name() + "对你道：“" HIR + ob->name() +
					NOR "这个败类打家劫舍，无恶不作，"
                                	"听说他最近在" + place +
					"，你去除掉他，提头来见我！”\n");
                } else
                if (me->is_bad())
                {
                        ob->set("shen", ob->query("combat_exp") / 2000);
                        tell_object(who, me->name() + "对你道：“" HIR + ob->name() + NOR
                                "这个所谓大侠屡次和我派作对，"
                                "听说他最近在" + place + "，你去宰"
                                "了他，提头来见！”\n");
                } else
                {
                        ob->set("shen_type", 0);
                        ob->set("shen", 0);
                        tell_object(who, me->name() + "对你道：“我早就看" HIR +
                                ob->name() + NOR "不顺眼，"
                                "听说他最近在" + place + "，你去做"
                                "了他，带他的人头来交差！”\n");
                }
                who->set("quest/type", "kill");
                switch (level)
                {
                case 0:
                        message_vision("$N顿了顿，又对$n道：“这个事情"
                                       "容易办得很，你要是还办不成那可不象话。”\n",
                                       me, who);
                        break;
                case 1:
                        break;
                case 2:
                        message_vision("$N看了看$n又道：“这个事情很是有些"
                                       "难办，你要是不行我就另找人吧。”\n",
                                       me, who);
                        break;
                case 3:
                        message_vision("$N叹了口气，郑重的对$n道：“这次"
                                       "任务凶险得紧，你不要勉强自己，不行就算了。”\n",
                                       me, who);
                        break;
                }

                if (level > 0 && random(10) == 1)
                {
                        string flee_msg;

                        // 随机重新放置NPC的位置
                        message_sort(CYN "$N" CYN "话音刚落，突然一人"
                                     "急急忙忙的赶了过来，喊道：“不"
                                     "好了，不好了，" HIR + ob->name() +
                                     NOR CYN "在" + place +
                                     "失踪了！现在不知道去了哪里！”"
                                     "$N" CYN "呆了半晌，这才对$n" CYN
                                     "道：“这事麻烦了，看来只有靠你自"
                                     "己努力了！”\n" NOR, me, who);
                        switch (random(3))
                        {
                        case 0:
                                flee_msg = "听说$N听到了江湖上追杀他的风"
                                           "声，已经躲到PLACE去了。";
                                break;
                        case 1:
                                flee_msg = "有人说$N就在咱们这地界呢，"
                                           "但是也有人说他在PLACE，不知道是真是假。";
                                break;
                        default:
                                flee_msg = "不知道...不知道...哦？好像"
                                           "听人说过是在PLACE。";
                                break;
                        }
                        ob->random_place(flee_msg);
                }
        }

        who->set("quest/family", fam);
        who->set("quest/master_name", me->name());
        who->set("quest/master_id", me->query("id"));
        who->set("quest/name", ob->name());
        who->set("quest/id", ob->query("id"));
        who->set("quest/level", level);
        who->set("quest/place", place);
        t = time();
        who->set("quest/time", t);
        t = time() / ONE_DAY;
        if (ob->query("place") == "西域")
                t += 8;
        else
                t += 4;
        t = t * ONE_DAY - 1;
        who->set("quest/limit", t);
        message("vision", me->name() + "在你耳边悄声说道：“你务必要在" +
                     CHINESE_D->chinese_monthday(t) + "之前完成！”\n", who);
        who->start_busy(1);
        return 1;
}

int accept_object(object me, object who, object ob)
{
        mapping q;              // WHO的任务
        string msg;             // 掌门说的消息
        object dob;             // 打晕敌人的人
        int bonus;              // 奖励(正整数，1是正常)
        int t;                  // 用来计算时间的变量
        int exp;                // 获得的经验
        int pot;                // 获得的潜能
        int mar;                // 获得的实战体会
        int weiwang;            // 获得的威望
        int score;              // 获得的江湖阅历
        int lvl;                // 人物的等级
        int quest_level;        // QUEST的等级
        int quest_count;        // 连续QUEST的数目
        int timeover;           // 标志：超时了？
        int added;              // 做任务的时候额外出现的敌人或敌人逃走
	mixed special = 0;      // 是否有特殊奖励

        if (me->query("family/family_name") != who->query("family/family_name"))
                return 0;

        q = who->query("quest");
        if (ob->is_letter())
        {
                if (ob->query("send_from") != me->query("id"))
                {
                        message_vision("$N道：“你要干什么？”\n", me);
                        return -1;
                }

                if (! q || q["type"] != "letter" || ob->query("send_to") != q["id"])
                {
                        message_vision("$N深深的叹了一口气，没说什么。\n", me);
                        destruct(ob);
                        return 1;
                }

                message_vision("$N瞪着$n道：“干什么？交给你的活你不打算干了？”\n",
                               me, who);        
                return -1;
        }

        if (ob->is_receipt())
        {
                if (ob->query("reply_to") != me->query("id"))
                {
                        message_vision("$N皱眉道：“给我这玩艺干什么？”\n", me);
                        return 0;
                }

                if (! q || q["type"] != "letter" || q["id"] != ob->query("reply_by"))
                {
                        message_vision("$N点点头道：“多谢了。”\n", me);
                        destruct(ob);
                        return 1;
                }

                msg = "$N接过" + ob->name() + "，仔细看了看，满意的说：“很好。”\n";
                t = time();
                if (t > q["limit"])
                {
                        msg += "$N叹了口气，又道：“可惜，不是让你" +
                               CHINESE_D->chinese_monthday(t) + "前做完吗？算"
                               "了，将功补过，你先退下吧。”\n";
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += "$N点点头道：“你很不错，这么快就完成了"
                                        "，好好干！”\n";
                        } else
                                msg += "$N点点头道：“这次不错，辛苦了。”\n";

                        timeover = 0;
                }
                bonus = (ob->query("receive_from") == who->query("id"));
                exp = 15 + random(10);
                pot = 5 + random(8);
                score = 6 + random(5);
                weiwang = 1;
                destruct(ob);
        } else
        {
                if (! mapp(q) || ! ob->is_corpse() && ! ob->is_head())
                        return 0;
        
                if (! stringp(ob->query("owner_id")))
                {
                        message_vision("$N捂着鼻子看了看" + ob->name() + "，道"
                                       "：“什么臭烘烘的？快给我拿走。”\n", me);
                        return 0;
                }
        
                if (ob->query("owner_id") != q["id"])
                        return 0;

                msg = "$N接过" + ob->name() + "，呵呵大笑，对$n道：“";
                if (me->is_good())
                        msg += "又除了一害，很好！";
                else
                if (me->is_bad())
                        msg += "好极了！什么大侠，不堪一击！";
                else
                        msg += "干得好，漂亮！";
                msg += "”\n";
                t = time();
                if (who->query_temp("quest/escape_times"))
                {
                        msg += "$N赞许道：“这次没想到敌人这么强悍，实在未曾料到，辛苦，辛苦！”\n";
                        timeover = 0;
                } else
                if (t > q["limit"])
                {
                        msg += "$N摇摇头，又道：“可惜，不是让你" +
                               CHINESE_D->chinese_monthday(t) + "前做完吗？算"
                               "了，将功补过，你先退下吧。”\n";
                        timeover = 1;
                } else
                {
                        if (t - q["time"] < ONE_DAY)
                        {
                                msg += "$N点点头道：“你很不错，这么快就完成了"
                                        "，好好干！”\n";
                        } else
                                msg += "$N点点头道：“这次不错，辛苦了。”\n";

                        timeover = 0;
                }

                // bonus为1表示正常奖励，为2表示扣除一半。
                bonus = (ob->query("killed_by") == who->query("id")) &&
                        (ob->query("defeated_by") == who ||
                         ! ob->query("defeated_by") &&
                           ob->query("defeated_by_who") == who->name(1));
                if (ob->query("assist") == who)
                {
                        dob = ob->query("defeated_by");
                        msg += "$N欣慰的对$n道：“这次你能够得到" +
                               (dob ? dob->name(1) : "同门师兄弟") +
                               "的帮忙，也属不易！以后彼此要多加照应！”\n";
                        bonus = 2;
                } else
                if (bonus)
                        bonus = 1;

                destruct(ob);
                lvl = NPC_D->check_level(who);
                exp = 10 + random(5) + lvl;
                pot = 5 + random(3) + lvl;
                weiwang = 2 + random(3) + lvl / 2;
                score = 2 + random(3) + lvl / 2;
                quest_count = who->query("quest_count") + 1;

                // add temped for keep compactible with old version
                if (who->query_temp("quest/total_count"))
                {
                        quest_count = who->query_temp("quest/total_count") + 1;
                        who->delete_temp("quest/total_count");
                }

                // 根据任务完成的次数修正奖励
                if (quest_count >= 500)
                {
                        // 连续完成了超过500次的任务
                        exp += 80 + random(quest_count / 20 + 1);
                        pot += 45 + random(quest_count / 25 + 1);
                        mar = 50 + random(20);
                        weiwang += 8 + random(20);
                        score += 4 + random(15);
                } else
                if (quest_count >= 200)
                {
                        // 连续完成了超过200次的任务
                        exp += 70 + random(quest_count / 20 + 1);
                        pot += 40 + random(quest_count / 25 + 1);
                        mar = 20 + random(10);
                        weiwang += 5 + random(15);
                        score += 3 + random(10);
                } else
                if (quest_count >= 100)
                {
                        // 连续完成了超过100次的任务
                        exp += 50 + random(quest_count / 20 + 1);
                        pot += 30 + random(quest_count / 25 + 1);
                        weiwang += 3 + random(10);
                        score += 2 + random(10);
                } else
                if (quest_count >= 10)
                {
                        // 连续完成了超过10次的任务
                        exp += 45 + random(quest_count / 20 + 1);
                        pot += 25 + random(quest_count / 25 + 1);
                        weiwang += 1 + random(5);
                        score += 1 + random(5);
                }

                switch (quest_level = q["level"])
                {
                case 0:
                        exp = exp / 2 + 1;
                        pot = pot / 2 + 1;
                        weiwang = weiwang / 3 + 1;
                        score = score / 4 + 1;
                        msg += "$N看着$n接着说道：“还行吧，下次我给你个难点的任务。”\n";
                        break;
                case 1:
                        msg += "$N对$n又道：“不错，看来我可以托付些重任给你了。”\n";
                        break;
                case 2:
                        exp += exp / 4;
                        pot += pot / 4;
                        weiwang += weiwang / 4;
                        score += score / 4;
                        msg += "$N对$n笑道：“真是不错，不愧是我们" +
                               who->query("family/family_name") +
                               "的矫矫者。”\n";
                        break;
                case 3:
                        exp += exp / 2;
                        pot += pot / 2;
                        weiwang += weiwang / 2;
                        score += score / 2;
                        msg += "$N赞许道：“非常不错，这次可给我们" +
                               who->query("family/family_name") +
                               "争脸了。”\n";
                        break;
                }

                if (quest_count == 100)
                {
                        msg += "$N哈哈大笑两声道：“真有你的，连着上百"
                               "次任务都完成的漂漂亮亮，很好，很好。”\n";
			special = 1;
                } else
                if (quest_count == 200)
                {
                        msg += "$N大喜道：“不错不错，真实不错，两百"
                               "次任务干得很好。”\n";
			special = "/clone/gift/puti-zi";
                } else
                if (quest_count == 500)
                {
                        msg += "$N叹道：“真是长江后浪推前浪，想不到你接连五百"
                               "次任务都无一疏漏，不易，不易！”\n";
			special = "/clone/gift/tianxiang";
                } else
                if (quest_count >= 1000)
                {
                        msg += "$N深深叹了口气，道：“想不到你连着上千次"
                               "任务无一失手，看来我们" + me->query("family/family_name") +
                               "真是后继有人啊！”\n";
			special = "/clone/gift/jiuzhuan";
                        quest_count = 0;
                } else
                if ((quest_count % 10) == 0)
                {
                        msg += "$N喜道：“真是不赖，居然连着" +
                               chinese_number(quest_count) +
                               "次都没有失手，干的好！”\n";
                }

                quest_level = q["level"];
                quest_level++;
                if (quest_level > MAX_QUEST_LEVEL)
                        quest_level = 1;

                who->set("quest_count", quest_count);
                who->set_temp("quest/next_level", quest_level);
        }

        if ((added = (int)who->query_temp("quest/help_count")) > 0)
        {
                msg += HIY "$N" HIY "又道：“这次敌人伏下帮手，而你能随"
                       "机应变，完成任务，可喜，可贺！”\n" NOR;
                who->delete_temp("quest/help_count");
        }
        added += (int)who->query_temp("quest/escape_times") * 2;
        who->delete_temp("quest/escape_times");
        // 根据NPC的帮手和逃走的次数调整经验
        if (added)
        {
                exp += exp * added / 2;
                pot += pot * added / 2;
        }

        message_vision(msg, me, who);
        who->delete("quest");
        if (! bonus) return 1;

        exp /= bonus;
        pot /= bonus;
        mar /= bonus;
        weiwang /= bonus;
        score /= bonus;
        // bouns
        if (timeover)
        {
                exp /= 2;
                pot /= 3;
                mar /= 2;
                weiwang /= 4;
                score /= 4;
        } else
        {
                // 0.01% to get a special object
                if (random(2000) == 1 || special)
			special_bonus(me, who, special);
        }

        bonus(who, ([ "exp" : exp, "pot" : pot, "mar" : mar,
                      "weiwang" : weiwang, "score" : score ]), 1);
        return 1;
}

int cancel_quest(object me, object who)
{
        mapping dbase;
        mapping q;
        object ob;
        string msg;
        int n;

        dbase = who->query_entire_dbase();
        if (! mapp(q = dbase["quest"]) ||
            q["master_id"] != me->query("id"))
                return notify_fail("我没给你什么任务啊？\n");

        switch (q["type"])
        {
        case "kill":
                if (q["notice"] == "die")
                {
                        message_vision("$N点点头，对$n道：“算了，听说这人"
                                       "已经被杀了，你不用再辛苦了。”\n",
                                       me, who);
                } else
                {
                        message_vision("$N摆摆手，对$n道：“你干不了就算了"
                                       "，让别人做吧！”\n",
                                       me, who);
                        who->delete("quest_count");
                }

	        who->delete_temp("quest/next_level");
                n = (40 + random(40) + NPC_D->check_level(who) * 5);
                // add temped for keep compactible with old version
                switch (q["level"])
                {
                case 0:
                        n *= 2;
                        break;
                case 1:
                        break;
                case 2:
                        n = 0;
                        break;
                case 3:
                        n = 0;
                        break;
                }
                if (! n) break;

                // adjust weiwang
                dbase["weiwang"] -= n;
                if (dbase["weiwang"] < 0)
                        dbase["weiwang"] = 0;
                msg = HIR "你的江湖威望受到了损失";

                // adjust experience
                if (dbase["experience"] > dbase["learned_experience"])
                {
                        dbase["experience"] += (dbase["learned_experience"] - dbase["experience"]) * 2 / 3;
                        msg += "，由于疲于奔命，你的实战体会难以及时消化吸收";
                }

                // notice place
                message("vision", msg + "。\n" NOR, who);
                break;

        case "letter":
                message_vision("$N叹口气，看了看$n道：“连这点小事都干不了？算了吧。”\n",
                               me, who);

                who->add("score", -(15 + random(10)));
                if (who->query("score") < 0)
                        who->set("score", 0);
                message("vision", HIG "你的江湖阅历受到了损失。\n" NOR, who);
                break;
        }
        who->start_busy(2);

        ob = find_living(q["id"]);
        map_delete(dbase, "quest");
        if (! ob || ob->query_temp("quester") != who->query("id"))
                return 1;

        if (environment(ob))
                message_vision("$N看了看四周，急急忙忙的走掉了。\n", ob);

        destruct(ob);
        return 1;
}

/***********************************************************
  系统注册任务概念

    HELL采用任务对象来管理众多各式各样的任务，而任务守护进程
就是他们的管理者。为什么需要任务对象？这是因为大部分任务都具
有类似的处理过程：收集情报，根据线索完成某些要求，实现最终任
务，获得奖励。为了能够快速的编写和实现多种任务，共享重复的实
现代码，系统规定了任务对象的格式，只要遵循任务对象的格式，就
可以快速的生成玩家任务。

    让我们首先看一下任务的结构：一个任务实际上就是一个自动机，
然后由玩家不断的触发这个自动机最后达到一个稳定状态，一般来说
就是任务成功或是终止。系统可以为任务对象制定一些标准事件，然
后由任务的设计者自己制定一些事件，这就组合成了一个任务的输入
事件，然后系统为任务维护一个状态，这样就构成了一个完整的自动
机。

    看一个简单的“杀人”任务。

    杀一个人主要需要三个要素：时间、地点、人物。在某一个时间，
某个地点出现一个人物，杀掉它就算完成，可以获得奖励。那么我们
设计的流程预期是这样的：一个人打听到了这个任务，就去相应的地
点，杀人，杀掉以后获得奖励。

    任务对象的自动机器：

                                      消息收集完全
            <原生态> -> 人物生成态 -----------+ 
                           /                  |
                 <Timeout>/    <Timeout>      |
                   -------<---------------\   |
                 /                         \  v
            <结束态>   <--------------- 人物出现态
                            杀死该人             

<原生态>和<结束态>是系统规定的状态，<Timeout> 是系统原先保留
的事件。而人物生成态和人物出现态是该任务特有的状态，另外消息
收集完全和杀死该人则是该任务对象特有的事件。

<原生态>阶段系统初始化任务对象，完成一些必要的操作，并将控制
权传递给任务对象以进行后续的操作。这时该任务就自动生成一个人
物，制定它的等级，正邪，预期出现的地点，打听的难度等等。然后
就进入到人物生成态，同时表明自己需要接受超时事件。

此时，玩家如果打听消息，有可能打听到这个任务，并经过反复打听，
获得了该人出现的地点信息，则该人物对象认为消息收集完全，就真
正的生成这个人物，等候玩家将它消灭。

如果该人物被消灭，则通知任务对象，人物对象转移到<结束态>。另
外一个进入结束态的可能是超时了。

进入<结束态>，系统自动清除该任务对象。

任务产生：这可以是游戏中的机关产生，故事产生，和系统随机产生
等等。只要调入一个对象，就可以产生任务。

任务消息：除了通常的消息，有一种消息即通过电脑控制的人物产生，
包括店小二和特殊的传递消息的人物，这些消息可以反映出当前任务
的一些信息，这些功能已经由系统封装。任务产生以后，系统调用接
口函数：register_information()来登记和任务相关的消息 -- 为什
么不在任务产生的同时由任务自己登记？这是因为任务守护进程有可
能析构后重新创建，这样将遗失所有登记的数据，此时任务守护进程
就会遍历系统中所有的任务，调用register_information()接口来重
新组织这些消息。

消息数据结构：

---+-- scheme(1) -*
   |
   +-- scheme(2) -*
   |
   +-- scheme(3) --+-- 关键字：消息1
                   |
                   +-- 关键字：消息2
                   |
                   .........

打听需要一定的江湖阅历，当random(江湖阅历) > 消息的时候， 就
有可能打听到这个消息。消息可能是一个函数，如果是这样的话，在
打听消息的时候系统把打听的对象和打听消息的人，关键字传递给该
函数，取它的返回结果。

QUEST_D提供的消息API：

QUEST_D->add_quest(QUEST_OBJECT);
QUEST_D->set_information(QUEST_OBJECT, key, information);
QUEST_D->query_information(QUEST_OBJECT, key);
QUEST_D->remove_information(QUEST_OBJECT, key);
QUEST_D->remove_all_information(QUEST_OBJECT);

QUEST_OB必须提供的消息接口：

QUEST_OB->register_information();
QUEST_OB->name();
QUEST_OB->can_know_by(object knower);
QUEST_OB->can_rumor_by(object knower);
QUEST_OB->query_introduce(object knower, object who);

***********************************************************/

// 系统增加一个任务
public void add_quest(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
        {
                // 原先没有任何任务
                total = ([ qob : 1 ]);
                set("information", total);
        } else
        {
                // 查看这个任务是否已经有定义
                if (undefinedp(total[qob]))
                        // 增加一个任务，因为这时候刚刚将任
                        // 务加入，还没有任何相关的具体信息，
                        // 所以这个条目对应的就只是一个简单
                        // 整数标识。
                        total[qob] = 1;
        }
}

// 设置消息
public void set_information(object qob, string key, mixed info)
{
        mapping total;
        mapping all_info;

        if (! stringp(key) || (! stringp(info) && ! functionp(info)))
        {
                log_file("static/quest",
                         sprintf("%s Quest:%O(%s) set illegal info:%s:%O.\n",
                                 log_time(), qob, qob->name(), key, info));
                return;
        }

        if (! mapp(total = query("information")))
                total = ([ ]);

        if (! mapp(all_info = total[qob]))
        {
                // 原先没有该任务对象的消息信息
                all_info = ([ ]);
                total += ([ qob : all_info ]);
        }

        all_info[key] = info;
        set("information", total);
}

// 查询消息
public mixed query_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return 0;

        if (! mapp(all_info = total[qob]))
                return 0;

        return all_info[key];
}

// 删除消息
public void remove_information(object qob, string key)
{
        mapping total;
        mapping all_info;

        if (! mapp(total = query("information")))
                return;

        if (! mapp(all_info = total[qob]))
                return;

        map_delete(all_info, key);
        if (! sizeof(all_info))
        {
                // 该任务对象已经没有消息了
                map_delete(total, qob);
                return;
        }
}

// 删除某一个对象的所有消息
public void remove_all_information(object qob)
{
        mapping total;

        if (! mapp(total = query("information")))
                return;

        // 在删除所有消息的同时，任务本身也去掉了 -- 为什么
        // 这样做，这是因为如果是一个没有任何消息的任务（仅
        // 靠任务介绍提供信息）调用这个函数的含义就是清除任
        // 务本身，而一个提供消息的任务清除所有消息也具有相
        // 同的含义。
        map_delete(total, qob);
}

// QUEST系统重新启动的时候收集所有任务对象的消息
private void collect_all_quest_information()
{
        mapping total;
        object qob;
        object *obs;

        CHANNEL_D->do_channel(this_object(), "sys",
                              "任务精灵开始收集所有的任务信息。");

        if (! mapp(total = query("information")))
        {
                total = ([ ]);
                set("information", total);
        }

        obs = filter_array(objects(), (: $1->is_quest() :));

        // 扫描所有的QUEST对象，登记信息
        foreach (qob in obs)
        {
                reset_eval_cost();
                total[qob] = 0;
                catch(qob->register_information());
        }

        // 唤醒几个子任务守护进程
        start_all_quest();
}

public void start_all_quest()
{
        string quest;
        string *qlist;
        string name;
        int pos;

        if (! VERSION_D->is_version_ok())
                // 正在同步版本？那么不启动任务守护进程
                return;

        quest = read_file(CONFIG_DIR "quest");
        if (! stringp(quest))
                // 配置文件中没有任务
                return;

        qlist = explode(quest, "\n");
        foreach (name in qlist)
        {
                // 防止运行超时
                reset_eval_cost();

                if (strlen(name) < 1 || name[0] == '#')
                        // 空行或者是注释行
                        continue;

                // 去掉行尾的注释和空格
                pos = strsrch(name, '#');
                if (pos > 1) name = name[0..pos - 1];
                name = replace_string(name, " ", "");

                // 生成文件名字
                name = QUEST_DIR + name + ".c";
                if (file_size(name) < 0)
                {
                        // 没有这个任务
                        log_file("static/quest",
                                 sprintf("%s invalid quest: %s\n",
                                         log_time(), name));
                        continue;
                }

                // 启动这个任务
                catch(call_other(name, "startup"));
        }
}

// 整理所有的任务
private void heart_beat()
{
        mapping total;
        mixed key;
        int live_time;
        int t;

        // 重新启动所有的任务进程：如果因为某种故障停止运行，
        // 此时可以将它们重新启动，如果他们原本没有出故障，
        // 那么此时重新启动会修改它们的心跳时间。
        start_all_quest();

        if (! mapp(total = query("information")))
                return;

        // 计算当前时间
        t = time();

        // 扫描所有的任务，只保留有效的任务
        foreach (key in keys(total))
        {
                reset_eval_cost();
                if (! objectp(key))
                        map_delete(total, key);
                else
                switch (key->query_status())
                {
                case QUEST_CREATE:
                        if (t - key->query("start_time") > QUEST_CREATE_PERIOD)
                        {
                                // 创建任务超过有效时间了，结束之
                                log_file("static/quest", sprintf("%s quest: %s create timeout\n%O",
                                                                 log_time(), base_name(key),
                                                                 key->query_entire_dbase()));
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;

                case QUEST_FINISH:
                        if (t->query("finish_time") > QUEST_FINISH_PERIOD)
                                // 结束任务超过有效时间了
                                key->change_status(QUEST_ERROR);
                        break;

                case QUEST_ERROR:
                        // 任务在运行错误状态中
                        break;

                default:
                        // 任务在通常运行状态中
                        if ((live_time = key->query("live_time")) > 0 &&
                            live_time < t - key->query("start_time"))
                        {
                                // 生存超过了时间
                                catch(key->change_status(QUEST_FINISH));
                                map_delete(total, key);
                        }
                        break;
                }
        }
}

// 供消息灵通人士调用使用
public string generate_information(object knower, object who, string topic)
{
        mapping total;
        object *obs;
        object *dest;
        string name, title;
        object last_ob;
        mixed answer;

        total = query("information");

        switch (random(30))
        {
        case 0:
                return "阿嚏！有点感冒，不好意思。";
        case 1:
                return "等...等等，你说什么？没听清楚。";
        case 2:
                return "嗯，稍等啊，就好... 好了，你刚才说啥？";
        case 3:
                return "这个... 这个... 哦，好了，啊？你问我呢？";
        case 4:
                return "唉呦！... 不好意思，是你问我么？";
        case 5:
                return "就好... 就好... 好了，你说啥？";
        case 7:
                return "!@#$%^&*";
        }

        if (topic == "rumor" || topic == "消息")
        {
                // 生成传闻
                if (! mapp(total) ||
                    ! sizeof(obs = filter_array(keys(total), (: objectp($1) :))))
                {
                        // 目前没有任何任务
                        switch (random(3))
                        {
                        case 0:
                                return "最近没啥消息。";
                        case 1:
                                return "好像最近挺太平的。";
                        default:
                                return "不知道...你去问问别人吧。";
                        }
                }

                // 过滤该小二可以散布的消息
                obs = filter_array(obs, (: objectp($1) && $1->can_rumor_by($(knower)) :));
                if (! sizeof(obs))
                {
                        // 该人士不能散布信息
                        switch (random(3))
                        {
                        case 0:
                                return "我倒是听说最近江湖上出了不少事儿。";
                        case 1:
                                return "哎呀呀！你也知道了一些秘密？快给我说说！";
                        default:
                                return "这年头，是越来越乱了。";
                        }
                }

                // 随机选择一个可以散布的任务消息
                last_ob = obs[random(sizeof(obs))];
                knower->set_temp("last_asked_quest", last_ob);
                if (answer = last_ob->query_prompt(knower, who))
                        return answer;

                switch (random(3))
                {
                case 0:
                        return "你可曾听过最近有关『" HIY +
                               last_ob->name() + NOR CYN "』的传闻？";
                case 1:
                        return "最近正在盛传『" HIY +
                               last_ob->name() + NOR CYN "』这件事情呢！";
                default:
                        return "你没有听到大家都在议论『" HIY +
                               last_ob->name() + NOR CYN "』吗？";
                }
        }

        if (! mapp(total))
                return 0;

        // 获得该人知道的所有任务信息
        obs = filter_array(keys(total), (: objectp($1) :));
        obs = filter_array(obs, (: $1->can_know_by($(knower)) :));

        // 查看是否问某一个任务的某一个条目
        if (sscanf(topic, "%s.%s", name, title) == 2)
        {
                dest = filter_array(obs, (: $1->name() == $(name) :));
                if (! sizeof(dest))
                        return 0;

                last_ob = dest[0];
        } else
        {
                // 查看是否问某一个任务
                dest = filter_array(obs, (: $1->name() == $(topic) :));
                if (sizeof(dest) > 0)
                {
                        last_ob = dest[0];
                        knower->set_temp("last_asked_quest", last_ob);
                        answer = last_ob->query_introduce(knower, who);
                        if (stringp(answer))
                                return answer;
                        return "你说的是" HIY + knower->name() +
                               HIY "那件事情吗？你问我算是问对人了。" NOR;
                } else
                // 查看最后一次被询问的任务消息中是否有该条目
                {
                        last_ob = knower->query_temp("last_asked_quest");
                        if (! objectp(last_ob) || ! mapp(total[last_ob]))
                                return 0;

                        title = topic;
                }
        }

        // 返回有关某个任务的某个条目的消息
        knower->set_temp("last_asked_quest", last_ob);
        answer = total[last_ob];

        if (! mapp(answer))
                return 0;

        // 这个任务登记了具体的信息
        answer = answer[title];
        if (functionp(answer))
                return evaluate(answer, knower, who, topic);

        if (stringp(answer))
                return answer;

        return 0;
}
