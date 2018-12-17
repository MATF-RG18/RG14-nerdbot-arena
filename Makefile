test: NBS1.c draw_bot.c draw_bot.h draw_trail.c draw_trail.h on_timer.c on_display.c on_display.c on_timer.h draw_anunaki.c draw_anunaki.h collision.c collision.h
	gcc -o test draw_bot.c on_timer.c on_display.c draw_anunaki.c draw_trail.c collision.c NBS1.c  -Wall -lGL -lGLU -lglut -lm

.PHONY: clean

clean:
	rm -rf *.o *~ test