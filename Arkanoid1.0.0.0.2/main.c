/*
    $$$$$\           $$\                                 $$$$$$$\                 $$\                     $$\                 
   \__$$ |          $$ |                                $$  __$$\                $$ |                    $$ |                
      $$ | $$$$$$\  $$$$$$$\   $$$$$$\   $$$$$$$\       $$ |  $$ |$$$$$$\   $$$$$$$ |$$\   $$\  $$$$$$$\ $$$$$$$\   $$$$$$\  
      $$ |$$  __$$\ $$  __$$\  \____$$\ $$  _____|      $$$$$$$  |\____$$\ $$  __$$ |$$ |  $$ |$$  _____|$$  __$$\  \____$$\ 
$$\   $$ |$$$$$$$$ |$$ |  $$ | $$$$$$$ |$$ /            $$  ____/ $$$$$$$ |$$ /  $$ |$$ |  $$ |$$ /      $$ |  $$ | $$$$$$$ |
$$ |  $$ |$$   ____|$$ |  $$ |$$  __$$ |$$ |            $$ |     $$  __$$ |$$ |  $$ |$$ |  $$ |$$ |      $$ |  $$ |$$  __$$ |
\$$$$$$  |\$$$$$$$\ $$$$$$$  |\$$$$$$$ |\$$$$$$$\       $$ |     \$$$$$$$ |\$$$$$$$ |\$$$$$$  |\$$$$$$$\ $$ |  $$ |\$$$$$$$ |
 \______/  \_______|\_______/  \_______| \_______|      \__|      \_______| \_______| \______/  \_______|\__|  \__| \_______|
                                                                                                                      
*/

#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/keyboard.h>
#include <stdbool.h>

struct Platform
{
    int x1;
    int y1;
    int x2;
    int y2;
};

int main(int argc, char* argv[])
{
    
    bool working = true;
    int width = 960;
    int height = 960;
    struct Platform New_Platform = { width / 2, height - 50,New_Platform.x1 + 100,New_Platform.y1 + 20 };
    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_EVENT_QUEUE* event_queue = NULL;

    if (!al_init()) {
        fprintf(stderr, "Failed to initialize allegro!\n");
        return -1;
    }

    display = al_create_display(width, height);
    if (!display) {
        fprintf(stderr, "Failed to create display!\n");
        return -1;
    }
    al_init_primitives_addon();
    al_install_keyboard();

    al_clear_to_color(al_map_rgb(0, 0, 0));                             //kolor tla
    al_flip_display();

    event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_keyboard_event_source());

    while (working)
    {
        al_draw_rectangle(1, 1, width*2/3, height, al_map_rgb(255, 255, 255), 4);
        ALLEGRO_EVENT ev;
        al_wait_for_event(event_queue, &ev);
        if(ev.type==ALLEGRO_EVENT_KEY_CHAR)
        {
            switch (ev.keyboard.keycode)
            {
            case ALLEGRO_KEY_LEFT:
                if (New_Platform.x1 > 0)
                {
                    New_Platform.x1 -= 5;
                    New_Platform.x2 -= 5;
                }
                break;
            case ALLEGRO_KEY_RIGHT:
                if (New_Platform.x2 < width * 2 / 3)
                {
                    New_Platform.x1 += 5;
                    New_Platform.x2 += 5;
                }
                    break;
            case ALLEGRO_KEY_ESCAPE:
                working = false;
                break;
            }
        }
        al_draw_filled_rectangle(New_Platform.x1, New_Platform.y1, New_Platform.x2, New_Platform.y2, al_map_rgb(255, 255, 255));
        al_flip_display();
        al_clear_to_color(al_map_rgb(0, 0, 0));
    }
    al_uninstall_keyboard();
    al_destroy_display(display);

    return 0;
}