//
// Created by David on 1/14/2025.
//

#ifndef ARRARYTOOLS_H
#define ARRARYTOOLS_H

/** @enum calendar_actions
 * @brief defines phrases relevant to the purpose of the program.
 */
enum calendar_actions {
    CREATE_EVENT = 1,
    EDIT_EVENT = 2,
    DELETE_EVENT = 3,
    PRINT_EVENT = 4,
    EXIT_CALENDAR = 5,
};

/**@typedef event_t calendartools.h
 * @brief Stores data about an event based on user input.
 * All values are to be user-defined.
 */
typedef struct {
    int id; ///calendar index of the event
    char name[33]; ///Name of the event with a 32-character limit.
    char location[33]; ///Location of the event with a 32-character limit.
    char date[11]; ///Date of the event with a 10-character limit. mm/dd/yyyy format to be used.
    char start_time[5]; ///Start time of event. HHmm format to be used, with no special characters.
    char end_time[5]; ///End time of event. HHmm format to be used, with no special characters.
} event_t;

extern event_t EMPTY;

/**
 * @typedef calendar_t calendartools.h
 * @brief A container to store an array of event_t types and the size of the array together.
 * @warning The size variable should be initialized to 0, and events should be empty with a size of 0, for ease of use with the rest of this header file.
 */
typedef struct {
    event_t *events; ///An array of events to be defined by the user.
    int size; 
} calendar_t;

/**
 * @brief Updates the value of event_id with the id of the target event.
 * @param [in] calendar The pointer to a calendar_t variable.
 * @param [out] event_id The pointer to the variable that will store the target event's id.
 */
void get_event_id(const calendar_t *calendar, int *event_id);

/**
 * @brief Prompts the user to enter the data of their new event to be stored.
 * @param [I/O] calendar The pointer of the calendar_t variable where the new event will be stored.
 */
void create_event(calendar_t *calendar);

/**
 * @brief Changes target event details based on user input.
 * @param [I/O] calendar The pointer of the calendar_t variable where the updated event will be stored.
 */
void edit_event(const calendar_t *calendar);

/**
 * @brief Replaced a target event with the EMPTY event.
 * @param [I/O] calendar The pointer of the calendar_t variable that has the target event.
 */
void delete_event(const calendar_t *calendar);

/**
 * @brief Print to console all data within a target event.
 * @param [in] calendar Pointer of a calendar_t variable that has the target event.
 * @param [in] event_id The array index of the target event.
 */
void print_event(const calendar_t *calendar, int event_id);

/**
 * @brief Gets calendar_t data from a previous session.
 * @param [I/O] calendar Pointer to a calendar_t variable.
 */
void get_session_data(calendar_t *calendar);

/**
 * @brief Store calendar_t data in a .txt file.
 * @param [in] calendar Pointer to a calendar_t variable.
 */
void write_session_data(const calendar_t *calendar);
#endif //ARRARYTOOLS_H