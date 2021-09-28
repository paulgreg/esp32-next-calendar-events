#define MAX_EVENTS 4

struct Events {
  unsigned int size;
  char date[MAX_EVENTS][25];
  char calendar[MAX_EVENTS][25];
  char summary[MAX_EVENTS][256];
};

boolean fillDataFromJson(JSONVar json, Events* events) {
  int size = json.length();
  for (int i = 0; i < size && i < MAX_EVENTS; i++) {
    sprintf(events->date[i], "%s", (const char*) json[i]["dateStart"]);
    sprintf(events->calendar[i], "%s", (const char*) json[i]["calendar"]);
    sprintf(events->summary[i], "%s", (const char*) json[i]["summary"]);
    events->size = i + 1;
  }
  return true;
}

/* events.json
[
  { "calendar":"","dateStart":"2021-09-25T00:00:00.000Z","summary":"", location: ""},
]
*/
