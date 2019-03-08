// ITEM Made by player(Ä³ÈË:moman) /data/item/m/moman-mylove.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 30 16:38:47 2001
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35mÌÒ»¨[1;34m´í[2;37;0m", ({ "mylove" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£

[1;35mÌÒ»¨[1;33m´øÓêÇ§°ãÑŞ£¬
[1;37mÁøĞõ[1;33mËæ·ç¼¸¶È¾­¡£

[1;37mÕâÊÇÒ»°Ñ[1;36mÈí½£¡£
[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÄ³ÈË(moman)
");
	set("value", 1);
	set("point", 181);
	set("material", "magic stone");
	set("wield_msg", "\n[1;37m$NÁè¿ÕÒ»Ö¸£¬[1;35mÌÒ»¨[1;34m´í[1;37mËæÊÖ¶ø³ö£¬ÉùÈçÁúÒ÷£¬ÍğÈôÒøºç£¬Ò«ÑÛÉÁÁÁ¡£\n[2;37;0m\n");
	set("unwield_msg", "\n[1;37m$NË«ÊÖÒ»ºÏ£¬ÒøºçÁ¢Òş£¬¹âÃ¢Á²¾Û£¬Ğëô§Ö®¼ä£¬[1;35mÌÒ»¨[1;34m´í[1;37mÏûÊ§ÎŞĞÎ¡£\n[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
