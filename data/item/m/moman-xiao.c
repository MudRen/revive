// ITEM Made by player(Ä³ÈË:moman) /data/item/m/moman-xiao.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 31 17:49:01 2001
#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32mÓñÏô[2;37;0m", ({ "xiao" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ö§");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ö§óï¡£

[1;32mÒ»Ö§´äÓñ×ö³ÉµÄ³¤Ïô£¬¾§Ó¨ÌŞÍ¸£¬Ò»¿´±ãÖª·ÇÈË¼ä·²Æ·¡£
[2;37;0m
óï±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÄ³ÈË(moman)
");
	set("value", 1);
	set("point", 181);
	set("material", "magic stone");
	set("wield_msg", "[1;37m$NÒÂÉÀÒ»Æ®£¬ÊÖÖĞÒÑ¶àÁËÒ»Ö§¾§Ó¨ÌŞÍ¸µÄ[2;37;0m[1;32mÓñÏô[2;37;0m[1;37m¡£[2;37;0m\n");
	set("unwield_msg", "[1;37m$NÊÖÍóÇá×ª£¬Õ£ÑÛ¼ä[2;37;0m[1;32mÓñÏô[2;37;0m[1;37mÒÑÈ»²»¼ûÓ°×Ù¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_xsword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
