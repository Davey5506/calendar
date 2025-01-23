# About Calendar
**Calendar** is a basic event management system. Which is capable of:
- Creating Events
- Editing Events
- Deleting Events
- Printing Events to the Console

# Data Management
**Calendar** uses a nested structure configuration to manage the data associated with the events inputted by the user.
<br/>
All events the user inputs are stored in an array that is dynamically allocated memory as needed.

## Post Runtime Data Management
**Calendar** will store all session data to a text file when the exit command is given by the user.<br/>
The fist line of the text file will contain the length of the array that was used to store the events.
Each following line will contain event data in the following order:
- Event ID
- Name
- Location
- Start Time
- End Time

>[!NOTE]
> [```void get_session_data(calendar_t *calendar);```](#get_session_data) reads from one event_t at a time from the text file.

# Code Documentation
This section gives an overview of each function, structure, and enumeration used in each file of the source code.<br/>
Function parameters will be marked with either, [in], [out], or [I/O] to denote the direction of data through it.

## calendarTools.h/c
### Functions
#### Public
```c++
void create_event(*calendar_t);
```
Prompts the user to enter the data of their new event to be stored.<br/>
Parameters:
- [I/O] calendar — The pointer of the calendar_t variable where the new event will be stored.
```c++
void edit_event(const *calendar_t);
```
Changes target event details based on user input.<br/>
Parameters:
- [I/O] calendar — The pointer of the calendar_t variable where the updated event will be stored.
```c++
void delete_event(const *calendar_t);
```
Replaced a target event with the EMPTY event.<br/>
Parameters: 
- [I/O] calendar — The pointer of the calendar_t variable that has the target event.
```c++
void print_event(const *calendar_t, int event_id);
```
Print to console all data within a target event.<br/>
Parameters:
- [in] calendar — Pointer of a calendar_t variable that has the target event.
- [in] event_id — The array index of the target event.
```c++
void get_event_id(const *calendar_t, int *event_id);
```
Updates the value of event_id with the id of the target event.<br/>
Parameters:
- [in] calendar — The pointer to a calendar_t variable.
- [out] event_id — The pointer to the variable that will store the target event's id.

<a name="get_session_data"></a>
```c++
void get_session_data(calendar_t *calendar);
```
Gets calendar_t data from a previous session.<br/>
Parameters:
- [I/O] calendar — Pointer to a calendar_t variable.
```c++
void write_session_data(const calendar_t *calendar);
```
Store calendar_t data in a .txt file.<br/>
Parameters:
- [in] calendar — Pointer to a calendar_t variable.
#### Private
```c++
void initialize_event(const calendar_t* calendar);
```
Sets newly created indices within the calendar parameter to [EMPTY](#Macros).<br/>
Params:
 - [I/O] calendar — A pointer to a calendar_t variable.
```c++
event_t* resize_calendar(calendar_t *calendar);
```
Expands the calendar, at the passed pointer, by the size of struct event_t.<br/>
Parameters:
- [in] calendar — a pointer to a calendar_t struct that contains a calendar of events.

Returns:
- event_t pointer that points to an expanded array of events.

### Structures
```c++
typedef calendar_t
```
A container to store an array of event_t types and the size of the array together.
>[!IMPORTANT]
> When using the calendar_t type, the size variable should be initialized to 0,
> and events should be empty with a size of 0, for ease of use with the rest of this header file

```c++
typedef event_t
```
Stores the following data about an event based on user input:
- ID (int)
- Name (char[33])
- Location (char[33])
- Date (char[11])
- Start Time (char[5])
- End Time (char[5])

>[!NOTE]
>For each element that is a character array type.
>The length is one character longer than needed to account for a null terminator.

>[!NOTE]
> An events ID is intended to be equal to its array index. 

### Macros
```c++
EMPTY
```
An event_t type with all fields equal to either 0 or "" depending on the field type.
### Enumerations
#### Public
```c++
enum calendar_actions {
    CREATE_EVENT = 1,
    EDIT_EVENT = 2,
    DELETE_EVENT = 3,
    PRINT_EVENT = 4,
    EXIT_CALENDAR = 5,
};
```
Defines phrases relevant to the purpose of the program.
#### Private
```c++
enum edit_actions {
    CHANGE_NAME = 1,
    CHANGE_LOCATION = 2,
    CHANGE_DATE = 3,
    CHANGE_TIME = 4,
    EXIT_EDIT = 5
};
```
Defines actions that are relevant to the edit_event function.
>[!IMPORTANT]
> enum edit_actions is in the local scope of the edit_event function, and not accessible elsewhere outside it.
## main.c
### Functions
```c++
int main(void);
```
The primary location where functions will be called from.
Task execution is handled by a switch statement that takes the return from ```int get_user_action(void);``` as input.
```c++
int get_user_action(void);
```
Prompts the user to enter an integer between 1 and 5 to carry out a certain function of the program.
```c++
void print_title_screen(void);
```
Prints an ascii art introduction to the console.
