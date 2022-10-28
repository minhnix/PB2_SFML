#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <string>
#include <time.h>
#include "../header/Manage.h"

using namespace sf;
using namespace std;

const Color backgroundColor(29, 33, 41);
const Color titleColor(239, 187, 53);
const Color contentColor(250, 235, 215);
const Color contentBgColor(38, 38, 38);

#define SELECT1 1
#define SELECT2 2
#define SELECT3 3
#define SELECT4 4
#define SELECTBUTTONEXIT 8
#define SELECTBUTTONOKE 13

void old()
{
  Clock clock;
  int timeRound, timeUp, hasRecord;
  Manage ql;
  RenderWindow window(VideoMode(2000, 1200), "Window", Style::Titlebar | Style::Close);
  Font font;
  font.loadFromFile("../assets/fonts/Nunito Regular.ttf");

  string _day, _hour, _state;

  Text day("Day:", font);
  day.setFillColor(contentColor);
  day.setPosition(0, 0);
  Text hour("Hour", font);
  hour.setFillColor(contentColor);
  hour.setPosition(0, 40);
  Text button("Check", font);
  button.setFillColor(contentColor);
  button.setPosition(0, 80);
  Text state("", font);
  state.setFillColor(contentColor);

  RectangleShape line(sf::Vector2f(1.6f, 30.f));
  line.setPosition((day.getPosition().x + day.getGlobalBounds().width + 5), 5);
  line.setFillColor(contentColor);
  int selected = 1;
  bool isValid = false;
  while (window.isOpen())
  {
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(contentColor);
    if (timeRound > 10000)
      elapsed = clock.restart();
    Event e;
    Vector2i pos = Mouse::getPosition(window);
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
      {
        window.close();
      }
      if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
      {
        if (pos.y >= 0 && pos.y < 40)
          selected = SELECT1;
        if (pos.y >= 40 && pos.y < 80)
          selected = SELECT2;
        if (pos.y >= 80 && pos.y < 120)
          selected = SELECTBUTTONOKE;
      }
      if (e.type == Event::TextEntered && e.text.unicode == 8)
        switch (selected)
        {
        case SELECT1:
          if (_day != "")
            _day.pop_back();
          break;
        case SELECT2:
          if (_hour != "")
            _hour.pop_back();
          break;
        default:
          break;
        }
      if (e.type == Event::TextEntered && e.text.unicode == 13)
        switch (selected)
        {
        case SELECT2:
          selected = SELECTBUTTONOKE;
          break;
        case SELECT1:
          selected = SELECT2;
          break;
        default:
          break;
        }
      if (e.type == Event::TextEntered && e.text.unicode < 128 && e.text.unicode != 13 && e.text.unicode != 8)
        switch (selected)
        {
        case SELECT1:
          _day += static_cast<char>(e.text.unicode);
          break;
        case SELECT2:
          _hour += static_cast<char>(e.text.unicode);
          break;
        default:
          break;
        }
      // set State
      day.setString("Day:" + _day);
      hour.setString("Hour:" + _hour);
      if (e.type == Event::TextEntered || e.type == Event::MouseButtonPressed)
        switch (selected)
        {
        case SELECT1:
          line.setPosition((day.getPosition().x + day.getGlobalBounds().width + 5), 5);
          isValid = false;
          break;
        case SELECT2:
          line.setPosition((hour.getPosition().x + hour.getGlobalBounds().width + 5), 45);
          isValid = false;
          break;
        case SELECTBUTTONOKE:
          line.setFillColor(Color::Transparent);
          if (_day != "")
          {
            isValid = true;
            hasRecord = 0;
          }
          else
            isValid = false;
          break;
        default:
          break;
        }
    }
    window.clear(backgroundColor);
    window.draw(line);
    window.draw(day);
    window.draw(hour);
    window.draw(button);

    if (isValid)
    {
      hasRecord = 0;
      time_t now = time(0), begin, end;
      tm *ltm = localtime(&now);
      int mday = atoi(_day.c_str());
      ltm->tm_mday = mday;
      if (_hour == "")
      {
        // begin
        ltm->tm_hour = 0;
        ltm->tm_min = 0;
        ltm->tm_sec = 0;
        begin = mktime(ltm);
        // end
        ltm->tm_hour = 23;
        ltm->tm_min = 59;
        ltm->tm_sec = 59;
        end = mktime(ltm);
      }
      else
      {
        ltm->tm_hour = atoi(_hour.c_str());
        ltm->tm_min = 0;
        ltm->tm_sec = 0;
        begin = mktime(ltm);
        ltm->tm_hour = atoi(_hour.c_str());
        ltm->tm_min = 59;
        ltm->tm_sec = 59;
        end = mktime(ltm);
      }
      for (int i = 0; i < ql.listRegister.length(); i++)
      {
        Record record = ql.listRegister.at(i);
        if (
            (record.getRegisteredAt() >= begin && record.getRegisteredAt() <= end) || // ở giữa
            (record.getRegisteredAt() < begin && record.getUnRegisteredAt() == 0) ||  // ở trước, chưa kết thúc
            (record.getRegisteredAt() < begin && record.getUnRegisteredAt() >= begin) // ở trước, kết thúc
        )
        {
          hasRecord++;
          long long timeStart = ql.listRegister.at(i).getRegisteredAt();
          long long timeFinish = ql.listRegister.at(i).getUnRegisteredAt();
          tm *ltmBegin = localtime(&timeStart);
          _state = "May" + ql.listRegister.at(i).getIdComputer() + " duoc su dung boi sinh vien " + ql.listRegister.at(i).getIdStudent() + " tu " + to_string(ltmBegin->tm_hour) + ":" + to_string(ltmBegin->tm_min) + ":" + to_string(ltmBegin->tm_sec) + " " + to_string(ltmBegin->tm_mday) + "/" + to_string(ltmBegin->tm_mon);
          if (timeFinish != 0)
          {
            tm *ltmEnd = localtime(&timeFinish);
            _state += " den " + to_string(ltmEnd->tm_hour) + ":" + to_string(ltmEnd->tm_min) + ":" + to_string(ltmEnd->tm_sec) + " " + to_string(ltmEnd->tm_mday) + "/" + to_string(ltmEnd->tm_mon);
          }
          state.setString(_state);
          state.setPosition(400, hasRecord * 50);
          window.draw(state);
        }
      }
    }

    window.display();
  }
}

// int main()
// {
//   Clock clock;
//   int time, timeUp;
//   Manage ql;
//   RenderWindow window(VideoMode(2000, 1200), "Window", Style::Titlebar | Style::Close);
//   Font font;
//   font.loadFromFile("../assets/fonts/Nunito Regular.ttf");
//   Text text;
//   text.setFillColor(contentColor);
//   text.setFont(font);
//   text.setString("TEST");
//   text.setPosition(0, 0);

//   Text title("List of computer", font);
//   title.setFillColor(contentColor);
//   title.setPosition(950, 0);

//   Text id("", font);
//   id.setFillColor(contentColor);
//   // id.setPosition(10, 40);

//   Text name("", font);
//   name.setFillColor(contentColor);
//   // name.setPosition(100, 40);

//   Text res("Register", font);
//   res.setFillColor(contentColor);
//   // res.setPosition(400, 40);

//   Text success("Register successfully", font);
//   success.setFillColor(Color::Transparent);
//   // success.setPosition(700, 40);

//   string mssv = "";
//   string userName = "";

//   Text MSSV("", font);
//   MSSV.setFillColor(backgroundColor);
//   MSSV.setPosition(370, 90);
//   Text USERNAME("", font);
//   USERNAME.setFillColor(backgroundColor);
//   USERNAME.setPosition(370, 180);
//   Text MESSAGE("", font);
//   MESSAGE.setFillColor(Color::White);
//   MESSAGE.setPosition(260, 240);

//   Text posX("", font);
//   posX.setFillColor(Color::White);
//   posX.setPosition(0, 0);
//   Text posY("", font);
//   posY.setFillColor(Color::White);
//   posY.setPosition(0, 30);

//   bool isClose = true;
//   while (window.isOpen())
//   {

//     int count = 0;
//     Event e;
//     Vector2i posClickedRes;
//     bool isRes = false;
//     while (window.pollEvent(e))
//     {
//       Vector2i pos = Mouse::getPosition(window);
//       posX.setString(to_string(pos.x));
//       posY.setString(to_string(pos.y));
//       if (e.type == Event::Closed)
//       {
//         window.close();
//       }
//       if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
//       {
//         if (pos.x >= 395 && pos.x <= 520 && !isRes)
//           posClickedRes = pos;
//       }
//     }
//     window.clear(backgroundColor);
//     window.draw(title);
//     for (int i = 0; i < ql.listComputer.length(); i++)
//     {
//       if (ql.listComputer.at(i).getStatus() == "not_using")
//       {
//         count++;
//         id.setString(ql.listComputer.at(i).getId());
//         id.setPosition(10, 50 * count);
//         name.setString(ql.listComputer.at(i).getName());
//         name.setPosition(100, 50 * count);
//         res.setPosition(400, 50 * count);
//         if (posClickedRes.y >= res.getPosition().y && posClickedRes.y <= res.getPosition().y + res.getGlobalBounds().height)
//         {
//           success.setPosition(700, 50 * count);
//           success.setFillColor(contentColor);
//         }
//         window.draw(success);
//         window.draw(id);
//         window.draw(name);
//         window.draw(res);
//         window.draw(posX);
//         window.draw(posY);
//       }
//     }
//     window.display();

//     if (mssv != "")
//     {
//       RectangleShape line(sf::Vector2f(1.6f, 30.f));
//       line.setPosition((MSSV.getPosition().x + MSSV.getGlobalBounds().width + 5), 94);
//       line.setFillColor(backgroundColor);
//       RenderWindow registerWindow(VideoMode(800, 360), "Sign in", Style::Titlebar | Style::Close);

//       Texture texture;
//       Sprite sprite;
//       texture.loadFromFile("../assets/images/sign_in.png");
//       sprite.setTexture(texture);
//       sprite.setTextureRect(IntRect(0, 0, 800, 360));
//       sprite.setPosition(0, 0);

//       int selected = 1;
//       while (registerWindow.isOpen())
//       {
//         Time elapsed = clock.getElapsedTime();
//         time = int((round(elapsed.asSeconds())));
//         timeUp = int(ceil(elapsed.asSeconds()));
//         if (time == timeUp)
//           line.setFillColor(Color::Transparent);
//         else
//           line.setFillColor(backgroundColor);
//         if (time > 10000)
//           elapsed = clock.restart();

//         Event eventRegister;
//         while (registerWindow.pollEvent(eventRegister))
//         {
//           if (eventRegister.type == Event::Closed)
//           {
//             registerWindow.close();
//           }
//           Vector2i pos = Mouse::getPosition(registerWindow);
//           posX.setString(to_string(pos.x));
//           posY.setString(to_string(pos.y));

//           if (eventRegister.type == Event::MouseButtonPressed && eventRegister.mouseButton.button == Mouse::Left)
//           {
//             if (pos.y > 80 && pos.y < 130)
//               selected = SELECT1;
//             if (pos.y > 170 && pos.y < 220)
//               selected = SELECT2;
//             if (pos.x >= 430 && pos.x <= 530 && pos.y <= 330 && pos.y >= 300)
//               selected = SELECTBUTTONOKE;
//           }
//           if (eventRegister.type == Event::TextEntered && eventRegister.text.unicode == 8)
//             switch (selected)
//             {
//             case SELECT1:
//               if (mssv != "")
//                 mssv.pop_back();
//               break;
//             case SELECT2:
//               if (userName != "")
//                 userName.pop_back();
//               break;
//             default:
//               break;
//             }
//           if (eventRegister.type == Event::TextEntered && eventRegister.text.unicode == 13)
//             switch (selected)
//             {
//             case SELECT2:
//               selected = SELECT3;
//               break;
//             case SELECT1:
//               selected = SELECT2;
//               break;
//             default:
//               break;
//             }
//           if (eventRegister.type == Event::TextEntered && eventRegister.text.unicode < 128 && eventRegister.text.unicode != 13 && eventRegister.text.unicode != 8)
//             switch (selected)
//             {
//             case SELECT1:
//               mssv += static_cast<char>(eventRegister.text.unicode);
//               break;
//             case SELECT2:
//               userName += static_cast<char>(eventRegister.text.unicode);
//               break;
//             default:
//               break;
//             }
//           MSSV.setString(mssv);
//           USERNAME.setString(userName);
//           if (eventRegister.type == Event::TextEntered || eventRegister.type == Event::MouseButtonPressed)
//             switch (selected)
//             {
//             case SELECT1:
//               line.setPosition((MSSV.getPosition().x + MSSV.getGlobalBounds().width + 5), 94);
//               break;
//             case SELECT2:
//               line.setPosition((USERNAME.getPosition().x + USERNAME.getGlobalBounds().width + 5), 184);
//               break;
//             case SELECTBUTTONOKE:
//               line.setFillColor(Color::Transparent);
//               if (mssv == "")
//               {
//                 MESSAGE.setString("Please enter your id");
//                 MESSAGE.setPosition(260, 240);
//               }
//               else if (ql.listStudent.indexOf(mssv) == -1 && userName == "")
//               {
//                 MESSAGE.setString("Please enter your name");
//                 MESSAGE.setPosition(250, 240);
//               }
//               else
//                 registerWindow.close();
//               break;
//             default:
//               break;
//             }
//         }

//         registerWindow.clear(backgroundColor);
//         registerWindow.draw(sprite); // first
//         registerWindow.draw(MESSAGE);
//         registerWindow.draw(line);
//         registerWindow.draw(MSSV);
//         registerWindow.draw(USERNAME);
//         registerWindow.draw(posX);
//         registerWindow.draw(posY);
//         registerWindow.display();
//       }
//     }
//   }
// }

// int main()
// {
//   sf::RenderWindow window(sf::VideoMode(2000, 1200), "Window", sf::Style::Titlebar | sf::Style::Close);
//   sf::Font arial;
//   arial.loadFromFile("../assets/fonts/Nunito Regular.ttf");
//   string s2 = "Text 2:";

//   Text t2(s2, arial);
//   t2.setFillColor(contentColor);
//   t2.setPosition(0, 40);

//   Text id, name;
//   id.setString("1");
//   id.setPosition(0, 160);
//   id.setFont(arial);
//   id.setFillColor(contentColor);
//   bool isTypingS = true;
//   bool isTypingS2 = false;
//   int selected = SELECT1;
//   RectangleShape input;
//   input.setSize(Vector2f(800, 40));
//   input.setFillColor(titleColor);
//   input.setPosition(0, 0);
//   RectangleShape line(sf::Vector2f(1.7f, 30.f));
//   line.setPosition((t.getPosition().x + t.getGlobalBounds().width + 5), 5);
//   line.setFillColor(contentColor);
//   Clock clock;
//   int time;
//   while (window.isOpen())
//   {
//     Time elapsed = clock.getElapsedTime();
//     time = int((floor(elapsed.asSeconds())));
//     if (time % 2 != 0)
//       line.setFillColor(Color::Transparent);
//     else
//       line.setFillColor(contentColor);
//     if (time > 10000)
//       elapsed = clock.restart();
//     sf::Event event;
//     while (window.pollEvent(event))
//     {
//       if (event.type == sf::Event::Closed)
//       {
//         window.close();
//       }
//       Vector2i pos = Mouse::getPosition(window);
//       if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
//       {
//         if (pos.y > 0 && pos.y < 40)
//           selected = SELECT1;
//         if (pos.y > 40 && pos.y < 80)
//           selected = SELECT2;
//       }
//       if (event.type == Event::TextEntered && event.text.unicode == 8)
//         switch (selected)
//         {
//         case SELECT1:
//           if (test.getName() != "This is text that you type:")
//             test.name.pop_back();
//           break;
//         case SELECT2:
//           if (s2 != "Text 2:")
//             s2.pop_back();
//           break;
//         default:
//           break;
//         }
//       if (event.type == Event::TextEntered && event.text.unicode == 13)
//         switch (selected)
//         {
//         case SELECT2:
//           selected = SELECT3;
//           break;
//         case SELECT1:
//           selected = SELECT2;
//           break;
//         default:
//           break;
//         }
//       if (event.type == Event::TextEntered && event.text.unicode < 128 && event.text.unicode != 13 && event.text.unicode != 8)
//         switch (selected)
//         {
//         case SELECT1:
//           test.name += static_cast<char>(event.text.unicode);
//           break;
//         case SELECT2:
//           s2 += static_cast<char>(event.text.unicode);
//           break;
//         default:
//           break;
//         }
//       t.setString(test.getName());
//       t2.setString(s2);
//       if (event.type == Event::TextEntered || event.type == Event::MouseButtonPressed)
//         switch (selected)
//         {
//         case SELECT1:
//           line.setPosition((t.getPosition().x + t.getGlobalBounds().width + 5), 5);
//           line.setFillColor(contentColor);
//           break;
//         case SELECT2:
//           line.setPosition((t2.getPosition().x + t2.getGlobalBounds().width + 5), 45);
//           line.setFillColor(contentColor);
//           break;
//         default:
//           break;
//         }
//     }
//     window.clear(backgroundColor);
//     window.draw(line);
//     window.draw(t);
//     window.draw(t2);
//     window.display();
//   }
//   return 0;
// }
