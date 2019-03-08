// ITEM Made by player(Ä½Èİ¼¦µ°:zeroz) /data/item/z/zeroz-egg.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 18:07:07 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("µ°¿Ç[2;37;0m", ({ "egg" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
Ä½Èİ¼¦µ°³öÉúºóÊ£ÏÂµÄ¶«¶«[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÄ½Èİ¼¦µ°(zeroz)
");
	set("value", 2100000);
	set("point", 190);
	set("material", "magic stone");
	set("wield_msg", "[1;31m$NÉíĞÎºöÈ»±äµÃ¹îÃØÒì³££¬½øÍËÖ®¼äÆ®ºö²»¶¨£¬ÁîÈËÎŞ´Ó×½Ãş¡£\n\n[1;37m$NÉí×ÓºöÇ°ºöºó£¬ºö×óºöÓÒ£¬Ò»²ã²ãÆøÀËµøå´·­Ó¿£¬»¤×¡È«Éí£¡\n\n[1;33m$NÉí×ÓºöÇ°ºöºó£¬ºö×óºöÓÒ£¬Ò»²ã²ãÆøÀËµøå´·­Ó¿£¬»¤×¡È«Éí£¡[2;37;0m\n");
	set("unwield_msg", "[1;37m$NÁ³É«Ò»º®¡¢ÈçÕÖ°×Ëª£¬·÷Ğä°ÁÈ»¶øÁ¢£¬ÍğÈôµÃµÀÕæÏÉ¡£\n\n[1;37m$NË«ÊÖÆ½¾Ù¹ı¶¥£¬ÔËÆğĞ¡ÎŞÏà¹¦£¬È«ÉíÁıÕÖÔÚ¾¢ÆøÖ®ÖĞ£¡\n\n[1;32m$N½«ÄÚÁ¦ÔË±é»ëÉíÖî´óÒªÑ¨£¬È»ºóÊÕÆøµ¤Ìï£¬Ë«Ä¿Ò»Õö£¬µÇÊ±¾«¹âËÄÉä£¡[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
