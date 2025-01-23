//
// Created by David on 1/14/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calendarTools.h"

/** @enum edit_actions
 * @brief Defines actions that are relevant to the edit_event function.
 * (See line 97 for use)
 */
enum edit_actions {
    CHANGE_NAME = 1,
    CHANGE_LOCATION = 2,
    CHANGE_DATE = 3,
    CHANGE_TIME = 4,
    EXIT_EDIT = 5
};


/** @struct event_t calendarTools.h
 * @brief EMPTY represents the default state of an event.
 * This definition is used to clear old data
 * from the stack and heap memory assigned to the program.
 */
struct event_t EMPTY = {
    .id = -1,
    .name = "",
    .location = "",
    .date = "",
    .start_time = "",
    .end_time = ""
};

/**@brief Expands the calendar, at the passed pointer, by the size of struct event_t.
 * @param [in] calendar a pointer to a calendar_t struct that contains a calendar of events.
 * @return event_t pointer that points to an expanded array of events.
 */
struct event_t * resize_calendar(struct calendar_t *calendar);

/**
 * @brief Sets newly created indexes to struct event_t EMPTY.
 * @param calendar A pointer to a calendar variable.
 * @return No value is explicitly returned, but events field of calendar is updated by reference.
 */
void initialize_event(const struct calendar_t* calendar);

void initialize_event(const struct calendar_t* calendar) {
    calendar->events[calendar->size - 1] = EMPTY;
}

void get_event_id(const struct calendar_t * calendar, int *event_id) {
    /// Get the name of the target event.
    char event_name[32];
    printf("Event name: ");
    scanf("%s", event_name);

    /// Check if the target event is in calendar.
    int idx = 0;
    for (; idx < calendar->size; idx++) {
        if (strcmp(calendar->events[idx].name, event_name) == 0) {
            *event_id = idx;
            break;
        }
    }
    if (*event_id == EMPTY.id) {
        printf("Event not found\n\n");
        return;
    }

    ///Update event_id by reference.
    *event_id = idx;
}

void create_event(struct calendar_t *calendar) {
    printf("Creating Event\n\n");
    /// Inintialize temporary event variable.
    struct event_t event = {
        .id = -1,
        .name = "",
        .location = "",
        .date = "",
        .start_time = "",
        .end_time = ""
    };

    /// Check for empty space in calendar's array.
    for (int idx = 0; idx < calendar->size; idx++) {
        if (calendar->events[idx].id == EMPTY.id) {
            event.id = idx;
            break;
        }
    }

    /// Expand calendar array if no space is available.
    if (event.id == EMPTY.id) {
        calendar->events = resize_calendar(calendar);
        event.id = calendar->size - 1;
        initialize_event(calendar);
    }

    /// Get event data from the user and store it in the temporary variable.
    printf("Name of event: ");
    scanf(" %s", event.name);

    printf("Location of event: ");
    scanf(" %s", event.location);

    printf("Date of event (mm/dd/yyyy): ");
    scanf(" %s", event.date);

    printf("Start time of event (hhmm): ");
    scanf(" %s", event.start_time);

    printf("End time of event (hhmm): ");
    scanf(" %s", event.end_time);

    /// Assign data the temporary event to calendar's array.
    calendar->events[event.id] = event;
}

void edit_event(const struct calendar_t *calendar) {
    printf("Edit Event\n\n");

    /// Get event name and check if it exsists.
    int event_id = -1;
    get_event_id(calendar, &event_id);
    if (event_id == EMPTY.id) {
        printf("Event not found\n");
        return;
    }

    /// Assign target event to a temporary variable.
    struct event_t event = calendar->events[event_id];
    print_event(calendar, event_id);

    /// Get user action.
    int action = 0;
    printf("Which element do you want to edit:\n"
           "1. Name\n"
           "2. Location\n"
           "3. Date\n"
           "4. Time\n"
           "5. Exit\n");
    scanf(" %d", &action);

    /// Get new event data based on previous user input.
    switch (action) {
        case CHANGE_NAME:
            printf("Enter new name: ");
            scanf("%s", &event.name);
            break;
        case CHANGE_LOCATION:
            printf("Enter new location: ");
            scanf("%s", &event.location);
            break;
        case CHANGE_DATE:
            printf("Enter new date: ");
            scanf("%s", &event.date);
            break;
        case CHANGE_TIME:
            printf("Enter new start time: ");
            scanf("%s", &event.start_time);
            printf("Enter new end time: ");
            scanf("%s", &event.end_time);
            break;
        case EXIT_EDIT:
            return;
        default:
            printf("Invalid action\n");
            break;
    }

    /// Assign new event data back to calendar's array.
    calendar->events[event.id] = event;
}

void delete_event(const struct calendar_t *calendar) {
    printf("Deleting Event\n\n");

    /// Get event name and check if it exsists.
    int event_id = -1;
    get_event_id(calendar, &event_id);
    if (event_id == EMPTY.id) {
        printf("Event not found\n");
        return;
    }

    /// Replace the target event with event_t EMPTY
    calendar->events[event_id] = EMPTY;
}

void print_event(const struct calendar_t *calendar, const int event_id) {
    ///Assign target event to a temporary variable.
    struct event_t event = calendar->events[event_id];

    /// Format and print event data.
    printf("Name: %s\n"
           "Location: %s\n"
           "Date: %s\n"
           "Start time: %s\n"
           "End time: %s\n\n", event.name, event.location, event.date, event.start_time, event.end_time);
}

struct event_t * resize_calendar(struct calendar_t * calendar) {
    /// Increase the size of the array in calendar by the size of event_t.
    calendar->size++;
    struct event_t* temp = realloc(calendar->events, sizeof(struct event_t) * calendar->size);

    /// Check if realloc failed.
    if (temp == NULL) {
        free(calendar);
        exit(1);
    }
    return temp;
}

void get_session_data(struct calendar_t *calendar) {
    FILE *file = fopen("sessionData.txt", "r");
    int event_count;

    if (file == NULL) {
        printf("No session data found\n");
        return;
    }

    fscanf(file, "%d", &event_count);
    if (event_count > 0) {
        for (int idx = 0; idx < event_count; idx++) {
            calendar->events = resize_calendar(calendar);
        }
    }

    for (int idx = 0; idx < event_count; idx++) {
        fscanf(file, "%d", &calendar->events[idx].id);
        fscanf(file, "%s", &calendar->events[idx].name);
        fscanf(file, "%s", &calendar->events[idx].location);
        fscanf(file, "%s", &calendar->events[idx].date);
        fscanf(file, "%s", &calendar->events[idx].start_time);
        fscanf(file, "%s", &calendar->events[idx].end_time);
    }
}

void write_session_data(const struct calendar_t *calendar) {
    FILE *file = fopen("sessionData.txt", "w");
    if (file == NULL) {
        printf("File could not be created.\n");
    }
    fprintf(file, "%d\n", calendar->size);

    for (int idx = 0; idx < calendar->size; idx++) {
        fprintf(file, "%d\n"
                      "%s\n"
                      "%s\n"
                      "%s\n"
                      "%s\n"
                      "%s\n",
                      calendar->events[idx].id,
                      calendar->events[idx].name,
                      calendar->events[idx].location,
                      calendar->events[idx].date,
                      calendar->events[idx].start_time,
                      calendar->events[idx].end_time);
    }
}