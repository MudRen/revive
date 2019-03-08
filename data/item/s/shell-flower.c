// ITEM Made by player(Ïæ¶ù:shell) /data/item/s/shell-flower.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Feb 08 14:15:27 2001
#include <ansi.h>
#include <weapon.h>

inherit BLADE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35mË®ÏÉ[2;37;0m", ({ "flower" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "°Ñ");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»°Ñµ¶¡£
[37mÏ£À°µÄÉñ£ºÎ÷Ë¹£¬°®ÉÏÁË×Ô¼ºÔÚË®ÖĞµÄµ¹Ó°£ºË®ÏÉ»¨£¬´Ó´ËËû²»»áÔÙ°®±ğÈË¡£[2;37;0m
µ¶±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÏæ¶ù(shell)
");
	set("value", 2100000);
	set("point", 190);
	set("material", "magic stone");
	set("wield_msg", "[1;35mË®ÖĞÔÂ\n¾µÖĞ»¨[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_blade(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
