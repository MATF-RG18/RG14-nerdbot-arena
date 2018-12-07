test: NBS1.c draw_bot.c draw_bot.h on_timer.c on_display.c on_display.c on_timer.h draw_trail.c draw_trail.h
	gcc -o test draw_bot.c on_timer.c on_display.c draw_trail.c NBS1.c  -Wall -lGL -lGLU -lglut -lm

.PHONY: clean

clean:
	rm -rf *.o *~ test