NAME=1KUSAI

SCREENMODE=1

$(NAME).dsk:: $(NAME).BIN

$(NAME).BIN: payload.zx7 dzx7_standard.asm
	vasmz80_oldstyle -o $@ dzx7_standard.asm -Fbin

payload.zx7: $(NAME).bin..text
	zx7 -i $< -o $@

$(NAME).bin..text:: intro.o

include build/cpc.mk
