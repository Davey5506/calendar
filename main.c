#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "calendarTools.h"

/**
 * @brief Get the desired action from the user.
 * @return The desired action of the user as an integer between 1 and 5.
 */
int get_user_action(void);

/**
 * @brief Prints to console, a welcome screen.
 */
void print_title_screen(void);

int main(void) {
    print_title_screen();

    event_t *events = {};
    calendar_t calendar = {
        .events = events,
        .size = 0
    };
    get_session_data(&calendar);

    bool run = true;
    while (run) {
        /// Call functions from calendarTools.h based on user input.
        switch (get_user_action()) {
            case CREATE_EVENT:
                create_event(&calendar);
            break;

            case EDIT_EVENT:
                if (calendar.size == 0) {
                    printf("Please create an event first.\n");
                    break;
                }
                edit_event(&calendar);
                break;

            case DELETE_EVENT:
                delete_event(&calendar);
                break;

            case PRINT_EVENT:
                int event_id = -1;
                get_event_id(&calendar, &event_id);
                if (event_id == EMPTY.id) {
                    printf("Event not found\n");
                    break;
                }
                print_event(&calendar,event_id);
                break;

            case EXIT_CALENDAR:
                write_session_data(&calendar);
                run = false;
                break;

            default:
                printf("Invalid action.\n");
                break;
        }
    }
    free(calendar.events);
}

int get_user_action(void) {
    printf("Please enter an action:\n"
           "1. Create Event\n"
           "2. Edit Event\n"
           "3. Delete Event\n"
           "4. Show Event\n"
           "5. Exit\n ");
    int action = 0;
    scanf("%d", &action);
    return action;
}

void print_title_screen(void) {
    printf(""
        " _______     _______     __         _________    ____  __    _________      _______     ______\n"
        "/  _____|   /   _   \\   |  |        |  ______|   |   \\ | |   |  ___   \\    /   _   \\   |   __  \\\n"
        "|  |        |  | |  |   |  |        |  |__       | |\\ \\| |   |  |   \\  |   |  | |  |   |  |__|  |\n"
        "|  |        |  |_|  |   |  |        |   __|      | | \\ \\ |   |  |   |  |   |  |_|  |   |       /\n"
        "|  |____    |  | |  |   |  |____    |  |_____    | |  \\  |   |  |___/  |   |  | |  |   |  |\\  \\\n"
        "\\_______|   |__| |__|   |_______|   |________|   |_|   \\_|   |________/    |__| |__|   |__| \\__\\\n");
}