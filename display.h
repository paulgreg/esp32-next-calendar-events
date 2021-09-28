#include "Fonts/FreeMono_euro9pt8b.h"
#include "Fonts/FreeMonoBold_euro9pt8b.h"
#include "Fonts/FreeMonoBold_euro12pt8b.h"

#define FONT_SMALL FreeMono_euro9pt8b
#define FONT_NORMAL FreeMonoBold_euro9pt8b
#define FONT_BIG FreeMonoBold_euro12pt8b

void drawBigText(int x, int y, char* text, int color) {
  display.setFont(&FONT_BIG);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

void drawSmallText(int x, int y, char* text, int color) {
  display.setFont(&FONT_SMALL);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

void drawText(int x, int y, char* text, int color) {
  display.setFont(&FONT_NORMAL);
  display.setTextColor(color);
  display.setCursor(x, y);
  display.print(text);
}

void extractDate (char* str, char* date) { // str is like 2021-09-25T00:00:00
  date[ 0] = str[8];
  date[ 1] = str[9];
  date[ 2] = '/';
  date[ 3] = str[5];
  date[ 4] = str[6];
  if (str[11] == '0' && str[12] == '0' && str[14] == '0' && str[15] == '0') {
    date[ 5] = '\0';
  } else {
    date[ 5] = ' ';
    date[ 6] = str[11];
    date[ 7] = str[12];
    date[ 8] = str[13];
    date[ 9] = str[14];
    date[10] = str[15];
    date[11] = '\0';
  }
}

void drawDateAndCalendar(int x, int y, char* fulldate, char* cal) {
  char calendarAndDate[25];
  char shortdate[14];
  extractDate(fulldate, shortdate);
  sprintf(calendarAndDate, "%s - %s", shortdate, cal);
  drawText(x, y, calendarAndDate, GxEPD_BLACK);
}

void drawSummary(int x, int y, char* text) {
  char summary[256];
  sprintf(summary, "%s", text);
  drawText(x, y, summary, GxEPD_RED);
}

void displayEvents(Events* events) {
  display.fillScreen(GxEPD_WHITE);
  display.firstPage();
  do {
    int x = 4;
    int y = 20;
    drawBigText(x, y, "Agenda", GxEPD_BLACK);
    y += 20;
    for (int i = 0; i < events->size; i++) {
      drawDateAndCalendar(x, y, events->date[i], events->calendar[i]);
      y += 17;
      drawSummary(x, y, events->summary[i]);
      y += 19;
    }
  } while (display.nextPage());
}

void displayError(char* text) {
  int x = 0;
  int y = display.height() - 20;
  int w = display.width() / 2;
  int h = 20;
  display.setFont(&FONT_SMALL);
  display.setTextColor(GxEPD_BLACK);
  
  display.setPartialWindow(x, y, w, h);
  display.firstPage();
  do
  {
    display.fillScreen(GxEPD_WHITE);
    display.setCursor(x + 2, y + 15);
    display.print(text);
  } while (display.nextPage());
}
