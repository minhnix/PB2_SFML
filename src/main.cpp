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
const Color vinhColor(250, 233, 108);

#define SELECT0 0
#define SELECT1 1
#define SELECT2 2
#define SELECT3 3
#define SELECT4 4
#define SELECTBUTTONEXIT 1234
#define SELECTBUTTONBACK 12345
#define SELECTBUTTONOKE 123456

RenderWindow window(VideoMode(2000, 1200), "PBL2", Style::Titlebar | Style::Close);
Manage ql;
Font font;
Texture bgHomeTexture, bgFunc1Texture, bgFunc6Texture, bgFunc7Texture, bgFunc8Texture, bgForm1Texture, bgForm2Texture, bgForm3Texture, bgForm4Texture, bgForm5Texture, bgForm6Texture, bgForm8Texture;

void loadAssets()
{
  font.loadFromFile("../assets/fonts/Nunito Regular.ttf");
  bgHomeTexture.loadFromFile("../assets/images/BG.png");
  bgFunc1Texture.loadFromFile("../assets/images/Func1.png");
  bgFunc6Texture.loadFromFile("../assets/images/Func6.png");
  bgFunc7Texture.loadFromFile("../assets/images/Func7.png");
  bgFunc8Texture.loadFromFile("../assets/images/Func8.png");
  bgForm1Texture.loadFromFile("../assets/images/Form1.png");
  bgForm2Texture.loadFromFile("../assets/images/Form2.png");
  bgForm3Texture.loadFromFile("../assets/images/Form3.png");
  bgForm4Texture.loadFromFile("../assets/images/Form4.png"); // 800 x 360
  bgForm5Texture.loadFromFile("../assets/images/Form5.png");
  bgForm6Texture.loadFromFile("../assets/images/Form6.png"); // 1500 x 460
  bgForm8Texture.loadFromFile("../assets/images/Form8.png");
}
void Home();
void textEnter(Event e, string &select1, string &select2, int &selected)
{
  if (e.type == Event::TextEntered && e.text.unicode == 8)
    switch (selected)
    {
    case SELECT1:
      if (select1 != "")
        select1.pop_back();
      break;
    case SELECT2:
      if (select2 != "")
        select2.pop_back();
      break;
    default:
      break;
    }
  if (e.type == Event::TextEntered && e.text.unicode == 13 && selected == SELECT1)
    selected = SELECT2;
  if (e.type == Event::TextEntered && e.text.unicode < 128 && e.text.unicode != 13 && e.text.unicode != 8)
    switch (selected)
    {
    case SELECT1:
      select1 += static_cast<char>(e.text.unicode);
      break;
    case SELECT2:
      select2 += static_cast<char>(e.text.unicode);
      break;
    default:
      break;
    }
}
void Func1()
{
  Sprite bgFunc1(bgFunc1Texture, IntRect(0, 0, 2000, 1200));
  Text _id("", font);
  _id.setFillColor(vinhColor);
  Text _name("", font);
  _name.setFillColor(vinhColor);
  Text _totalTime("", font);
  _totalTime.setFillColor(vinhColor);
  Text _register("", font);
  _register.setFillColor(vinhColor);

  while (window.isOpen())
  {
    Event e;
    Vector2i pos = Mouse::getPosition(window);
    Vector2i posClickedRegister;
    while (window.pollEvent(e))
    {
      int count = 0;
      if (e.type == Event::Closed)
        window.close();
      if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
      {
        if (pos.x >= 0 && pos.x <= 210 && pos.y >= 1130 && pos.y <= 1190)
          Home();
        if (pos.x >= 1600 && pos.x <= 1900)
          posClickedRegister = pos;
      }
      window.clear();
      window.draw(bgFunc1);
      for (int i = 0; i < ql.listComputer.length(); i++)
      {
        if (ql.listComputer.at(i).getStatus() == "not_using")
        {
          count++;
          _id.setString(ql.listComputer.at(i).getId());
          _id.setPosition(155, 200 + 40 * count);
          _name.setString(ql.listComputer.at(i).getName());
          _name.setPosition(450, 200 + 40 * count);
          _totalTime.setString(to_string(ql.listComputer.at(i).getTimeUsed()));
          _totalTime.setPosition(1150, 200 + 40 * count);
          _register.setString("Register");
          _register.setPosition(1670, 200 + 40 * count);
          if (posClickedRegister.y >= _register.getPosition().y && posClickedRegister.y <= _register.getPosition().y + _register.getGlobalBounds().height)
          {
            posClickedRegister.x = 0;
            posClickedRegister.y = 0;
            RenderWindow registerWindow(VideoMode(800, 360), "Register", Style::Titlebar | Style::Close);
            Sprite bgForm1(bgForm1Texture, IntRect(0, 0, 800, 360));
            Clock clock;
            int timeRound, timeUp;
            string id, name;
            Text __id("", font);
            __id.setFillColor(Color::Black);
            __id.setPosition(395, 90);
            Text __name("", font);
            __name.setFillColor(Color::Black);
            __name.setPosition(395, 180);
            Text message("", font);
            message.setFillColor(vinhColor);
            RectangleShape line(Vector2f(1.6f, 30.f));
            line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 94);
            line.setFillColor(Color::Black);
            int selected = 1;
            bool isValid = false;
            while (registerWindow.isOpen())
            {
              isValid = false;
              Vector2i posRegister = Mouse::getPosition(registerWindow);
              Time elapsed = clock.getElapsedTime();
              timeRound = int((round(elapsed.asSeconds())));
              timeUp = int(ceil(elapsed.asSeconds()));
              if (timeRound == timeUp)
                line.setFillColor(Color::Transparent);
              else
                line.setFillColor(Color::Black);
              if (timeRound > 10000)
                elapsed = clock.restart();
              if (selected == SELECT0)
              {
                line.setFillColor(Color::Transparent);
              }
              Event eventRegister;
              while (registerWindow.pollEvent(eventRegister))
              {
                if (eventRegister.type == Event::Closed)
                  registerWindow.close();
                if (eventRegister.type == Event::MouseButtonPressed && eventRegister.mouseButton.button == Mouse::Left)
                {
                  if (posRegister.y >= 90 && posRegister.y <= 125)
                    selected = SELECT1;
                  if (posRegister.y >= 180 && posRegister.y <= 215)
                    selected = SELECT2;
                  if (posRegister.x >= 430 && posRegister.x <= 530 && posRegister.y >= 300 && posRegister.y <= 330)
                    selected = SELECTBUTTONOKE;
                  if (posRegister.x >= 270 && posRegister.x <= 370 && posRegister.y >= 300 && posRegister.y <= 330)
                    selected = SELECTBUTTONEXIT;
                }
                textEnter(eventRegister, id, name, selected); //
                __id.setString(id);
                __name.setString(name);
                if (eventRegister.type == Event::TextEntered || eventRegister.type == Event::MouseButtonPressed)
                  switch (selected)
                  {
                  case SELECT1:
                    line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 94);
                    break;
                  case SELECT2:
                    line.setPosition((__name.getPosition().x + __name.getGlobalBounds().width + 5), 184);
                    break;
                  case SELECTBUTTONOKE:
                    selected = SELECT0;
                    line.setFillColor(Color::Transparent);
                    if (id == "")
                    {
                      message.setString("Please enter student id");
                      message.setPosition(230, 240);
                    }
                    else if (ql.listStudent.indexOf(id) == -1 && name == "")
                    {
                      message.setString("Please enter student name");
                      message.setPosition(210, 240);
                    }
                    else if (ql.listStudent.indexOf(id) != -1 && name != ql.listStudent.at(ql.listStudent.indexOf(id)).getName() && name != "")
                    {
                      message.setString("Please check student name");
                      message.setPosition(210, 240);
                    }
                    else
                    {
                      bool used = false;
                      for (int index = 0; index < ql.listComputer.length(); index++)
                        if (id == ql.listComputer.at(index).getIdStudent())
                        {
                          used = true;
                          break;
                        }
                      if (!used)
                      {
                        isValid = true;
                        message.setString("Register successfully");
                        message.setPosition(240, 240);
                      }
                      else
                      {
                        message.setString("Student is using computer");
                        message.setPosition(220, 240);
                      }
                    }
                    break;
                  case SELECTBUTTONEXIT:
                    registerWindow.close();
                    break;
                  default:
                    break;
                  }
              }
              registerWindow.clear();
              registerWindow.draw(bgForm1);
              registerWindow.draw(__id);
              registerWindow.draw(__name);
              registerWindow.draw(line);
              registerWindow.draw(message);
              registerWindow.display();
              if (isValid)
              {
                time_t now = time(0);
                if (ql.listStudent.indexOf(id) == -1)
                {
                  ql.listStudent.add(Student(id, name));
                  ql.dbStudent.Create(Student(id, name));
                }
                ql.listComputer.at(i).setStatus("using");
                ql.dbComputer.Update(i, "status", "using");
                ql.listComputer.at(i).setIdStudent(id);
                ql.dbComputer.Update(i, "idStudent", id.c_str());
                ql.listRegister.add(Record(ql.listComputer.at(i).getId(), id, now, 0));
                ql.dbRegister.Create(Record(ql.listComputer.at(i).getId(), id, now, 0));
                clock.restart();
                while (clock.getElapsedTime().asSeconds() <= 1)
                  selected = 0;
                registerWindow.close();
              }
            }
          }
          window.draw(_id);
          window.draw(_name);
          window.draw(_totalTime);
          window.draw(_register);
        }
      }
      window.display();
    }
  }
}
void Func2()
{
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  RenderWindow unRegisterWindow(VideoMode(800, 360), "Unregister", Style::Titlebar | Style::Close);
  Sprite bgForm2(bgForm2Texture, IntRect(0, 0, 800, 360));
  Clock clock;
  int timeRound, timeUp, indexRegister;
  string id, temp, idComputer;
  Text __id("", font);
  __id.setFillColor(Color::Black);
  __id.setPosition(385, 150);
  Text message("", font);
  message.setFillColor(vinhColor);
  message.setPosition(210, 240);
  RectangleShape line(Vector2f(1.6f, 30.f));
  line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 154);
  line.setFillColor(Color::Black);
  int selected = 1;
  bool isValid = false;
  while (unRegisterWindow.isOpen())
  {
    isValid = false;
    Vector2i posUnRegister = Mouse::getPosition(unRegisterWindow);
    posX.setString(to_string(posUnRegister.x));
    posY.setString(to_string(posUnRegister.y));
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(Color::Black);
    if (timeRound > 10000)
      elapsed = clock.restart();
    if (selected == 0)
    {
      line.setFillColor(Color::Transparent);
    }
    Event eventUnRegister;
    while (unRegisterWindow.pollEvent(eventUnRegister))
    {
      if (eventUnRegister.type == Event::Closed)
        unRegisterWindow.close();
      if (eventUnRegister.type == Event::MouseButtonPressed && eventUnRegister.mouseButton.button == Mouse::Left)
      {
        if (posUnRegister.y >= 150 && posUnRegister.y <= 185)
          selected = SELECT1;
        if (posUnRegister.x >= 430 && posUnRegister.x <= 530 && posUnRegister.y >= 300 && posUnRegister.y <= 330)
          selected = SELECTBUTTONOKE;
        if (posUnRegister.x >= 270 && posUnRegister.x <= 370 && posUnRegister.y >= 300 && posUnRegister.y <= 330)
          selected = SELECTBUTTONEXIT;
      }
      textEnter(eventUnRegister, id, temp, selected);
      __id.setString(id);
      if (eventUnRegister.type == Event::TextEntered || eventUnRegister.type == Event::MouseButtonPressed)
      {
        switch (selected)
        {
        case SELECT1:
          line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 154);
          break;
        case SELECTBUTTONOKE:
          selected = SELECT0;
          line.setFillColor(Color::Transparent);
          if (id == "")
          {
            message.setString("Please enter student id");
            message.setPosition(230, 240);
          }
          else if (ql.listStudent.indexOf(id) == -1)
          {
            message.setString("Student id do not exist");
            message.setPosition(230, 240);
          }
          else
          {
            bool used = false;
            for (int i = 0; i < ql.listRegister.length(); i++)
            {
              if (id == ql.listRegister.at(i).getIdStudent() && ql.listRegister.at(i).getUnRegisteredAt() == 0)
              {
                used = true;
                indexRegister = i;
                idComputer = ql.listRegister.at(i).getIdComputer();
                break;
              }
            }
            if (used)
            {
              isValid = true;
              message.setString("Unregister successfully");
              message.setPosition(240, 240);
            }
            else
            {
              message.setString("Student is not using computer");
              message.setPosition(190, 240);
            }
          }
          break;
        case SELECTBUTTONEXIT:
          unRegisterWindow.close();
          break;
        default:
          break;
        }
      }
    }
    unRegisterWindow.clear();
    unRegisterWindow.draw(bgForm2);
    unRegisterWindow.draw(line);
    unRegisterWindow.draw(__id);
    unRegisterWindow.draw(message);
    unRegisterWindow.draw(posX);
    unRegisterWindow.draw(posY);
    unRegisterWindow.display();
    time_t now = time(0);
    if (isValid)
    {
      time_t now = time(0);
      int indexComputer = ql.listComputer.indexOf(idComputer);
      long long timeUsed = ql.listComputer.at(indexComputer).getTimeUsed() + (now - ql.listRegister.at(indexRegister).getRegisteredAt());
      ql.listRegister.at(indexRegister).setUnRegisterAt(now);     // update unRegistered time
      ql.dbRegister.Update(indexRegister, "unRegisteredAt", now); // save database
      ql.listComputer.at(indexComputer).setTimeUsed(timeUsed);    // update timeUsed Computer
      ql.dbComputer.Update(indexComputer, "timeUsed", timeUsed);  // save database
      ql.listComputer.at(indexComputer).setIdStudent("");
      ql.dbComputer.Update(indexComputer, "idStudent", "");
      ql.listComputer.at(indexComputer).setStatus("not_using");
      ql.dbComputer.Update(indexComputer, "status", "not_using");
      clock.restart();
      while (clock.getElapsedTime().asSeconds() <= 1)
        selected = 0;
      unRegisterWindow.close();
    }
  }
}
void Func3()
{
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  RenderWindow createWindow(VideoMode(800, 360), "Create", Style::Titlebar | Style::Close);
  Sprite bgForm3(bgForm3Texture, IntRect(0, 0, 800, 360));
  Clock clock;
  int timeRound, timeUp;
  string id, name;
  Text __id("", font);
  __id.setFillColor(Color::Black);
  __id.setPosition(388, 100);
  Text __name("", font);
  __name.setFillColor(Color::Black);
  __name.setPosition(388, 177);
  Text message("", font);
  message.setFillColor(vinhColor);
  RectangleShape line(Vector2f(1.6f, 30.f));
  line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 104);
  line.setFillColor(Color::Black);
  int selected = 1;
  bool isValid = false;
  while (createWindow.isOpen())
  {
    isValid = false;
    Vector2i posCreate = Mouse::getPosition(createWindow);
    posX.setString(to_string(posCreate.x));
    posY.setString(to_string(posCreate.y));
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(Color::Black);
    if (timeRound > 10000)
      elapsed = clock.restart();
    if (selected == SELECT0)
    {
      line.setFillColor(Color::Transparent);
    }
    Event eventCreate;
    while (createWindow.pollEvent(eventCreate))
    {
      if (eventCreate.type == Event::Closed)
        createWindow.close();
      if (eventCreate.type == Event::MouseButtonPressed && eventCreate.mouseButton.button == Mouse::Left)
      {
        if (posCreate.y >= 100 && posCreate.y <= 135)
          selected = SELECT1;
        if (posCreate.y >= 180 && posCreate.y <= 215)
          selected = SELECT2;
        if (posCreate.x >= 430 && posCreate.x <= 530 && posCreate.y >= 300 && posCreate.y <= 330)
          selected = SELECTBUTTONOKE;
        if (posCreate.x >= 270 && posCreate.x <= 370 && posCreate.y >= 300 && posCreate.y <= 330)
          selected = SELECTBUTTONEXIT;
      }
      textEnter(eventCreate, id, name, selected); //
      __id.setString(id);
      __name.setString(name);
      if (eventCreate.type == Event::TextEntered || eventCreate.type == Event::MouseButtonPressed)
        switch (selected)
        {
        case SELECT1:
          line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 104);
          break;
        case SELECT2:
          line.setPosition((__name.getPosition().x + __name.getGlobalBounds().width + 5), 181);
          break;
        case SELECTBUTTONOKE:
          selected = SELECT0;
          line.setFillColor(Color::Transparent);
          if (id == "")
          {
            message.setString("Please enter computer id");
            message.setPosition(220, 240);
          }
          else if (ql.listComputer.indexOf(id) == -1 && name == "")
          {
            message.setString("Please enter computer name");
            message.setPosition(200, 240);
          }
          else if (ql.listComputer.indexOf(id) != -1)
          {
            message.setString("Computer id exists");
            message.setPosition(270, 240);
          }
          else
          {
            isValid = true;
            message.setString("Create successfully");
            message.setPosition(250, 240);
          }
          break;
        case SELECTBUTTONEXIT:
          createWindow.close();
          break;
        default:
          break;
        }
    }
    createWindow.clear();
    createWindow.draw(bgForm3);
    createWindow.draw(__id);
    createWindow.draw(__name);
    createWindow.draw(line);
    createWindow.draw(posX);
    createWindow.draw(posY);
    createWindow.draw(message);
    createWindow.display();
    if (isValid)
    {
      Computer computer(id, name, "not_using", "", 0);
      ql.listComputer.add(computer);
      ql.dbComputer.Create(computer);
      clock.restart();
      while (clock.getElapsedTime().asSeconds() <= 1)
        selected = 0;
      createWindow.close();
    }
  }
}
void Func4()
{
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  RenderWindow updateWindow(VideoMode(800, 360), "Update", Style::Titlebar | Style::Close);
  Sprite bgForm4(bgForm4Texture, IntRect(0, 0, 800, 360));
  Clock clock;
  int timeRound, timeUp;
  string id, name;
  Text __id("", font);
  __id.setFillColor(Color::Black);
  __id.setPosition(388, 100);
  Text __name("", font);
  __name.setFillColor(Color::Black);
  __name.setPosition(388, 177);
  Text message("", font);
  message.setFillColor(vinhColor);
  RectangleShape line(Vector2f(1.6f, 30.f));
  line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 104);
  line.setFillColor(Color::Black);
  int selected = 1;
  bool isValid = false;
  while (updateWindow.isOpen())
  {
    isValid = false;
    Vector2i posUpdate = Mouse::getPosition(updateWindow);
    posX.setString(to_string(posUpdate.x));
    posY.setString(to_string(posUpdate.y));
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(Color::Black);
    if (timeRound > 10000)
      elapsed = clock.restart();
    if (selected == SELECT0)
    {
      line.setFillColor(Color::Transparent);
    }
    Event eventUpdate;
    while (updateWindow.pollEvent(eventUpdate))
    {
      if (eventUpdate.type == Event::Closed)
        updateWindow.close();
      if (eventUpdate.type == Event::MouseButtonPressed && eventUpdate.mouseButton.button == Mouse::Left)
      {
        if (posUpdate.y >= 100 && posUpdate.y <= 135)
          selected = SELECT1;
        if (posUpdate.y >= 180 && posUpdate.y <= 215)
          selected = SELECT2;
        if (posUpdate.x >= 430 && posUpdate.x <= 530 && posUpdate.y >= 300 && posUpdate.y <= 330)
          selected = SELECTBUTTONOKE;
        if (posUpdate.x >= 270 && posUpdate.x <= 370 && posUpdate.y >= 300 && posUpdate.y <= 330)
          selected = SELECTBUTTONEXIT;
      }
      textEnter(eventUpdate, id, name, selected); //
      __id.setString(id);
      __name.setString(name);
      if (eventUpdate.type == Event::TextEntered || eventUpdate.type == Event::MouseButtonPressed)
        switch (selected)
        {
        case SELECT1:
          line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 104);
          break;
        case SELECT2:
          line.setPosition((__name.getPosition().x + __name.getGlobalBounds().width + 5), 181);
          break;
        case SELECTBUTTONOKE:
          selected = SELECT0;
          line.setFillColor(Color::Transparent);
          if (id == "")
          {
            message.setString("Please enter computer id");
            message.setPosition(220, 240);
          }
          else if (ql.listComputer.indexOf(id) == -1)
          {
            message.setString("Computer id do not exist");
            message.setPosition(220, 240);
          }
          else if (ql.listComputer.indexOf(id) != -1 && name == "")
          {
            message.setString("Please enter computer name");
            message.setPosition(200, 240);
          }
          else
          {
            isValid = true;
            message.setString("Update successfully");
            message.setPosition(245, 240);
          }
          break;
        case SELECTBUTTONEXIT:
          updateWindow.close();
          break;
        default:
          break;
        }
    }
    updateWindow.clear();
    updateWindow.draw(bgForm4);
    updateWindow.draw(__id);
    updateWindow.draw(__name);
    updateWindow.draw(line);
    updateWindow.draw(posX);
    updateWindow.draw(posY);
    updateWindow.draw(message);
    updateWindow.display();
    if (isValid)
    {
      int index = ql.listComputer.indexOf(id);
      ql.listComputer.at(index).setName(name);
      ql.dbComputer.Update(index, "name", name.c_str());
      clock.restart();
      while (clock.getElapsedTime().asSeconds() <= 1)
        selected = 0;
      updateWindow.close();
    }
  }
}
void Func5()
{
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  RenderWindow deleteWindow(VideoMode(800, 360), "Delete", Style::Titlebar | Style::Close);
  Sprite bgForm5(bgForm5Texture, IntRect(0, 0, 800, 360));
  Clock clock;
  int timeRound, timeUp;
  string id, name;
  Text __id("", font);
  __id.setFillColor(Color::Black);
  __id.setPosition(385, 150);
  Text message("", font);
  message.setFillColor(vinhColor);
  RectangleShape line(Vector2f(1.6f, 30.f));
  line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 154);
  line.setFillColor(Color::Black);
  int selected = 1;
  bool isValid = false;
  while (deleteWindow.isOpen())
  {
    isValid = false;
    Vector2i posDelete = Mouse::getPosition(deleteWindow);
    posX.setString(to_string(posDelete.x));
    posY.setString(to_string(posDelete.y));
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(Color::Black);
    if (timeRound > 10000)
      elapsed = clock.restart();
    if (selected == SELECT0)
    {
      line.setFillColor(Color::Transparent);
    }
    Event eventDelete;
    while (deleteWindow.pollEvent(eventDelete))
    {
      if (eventDelete.type == Event::Closed)
        deleteWindow.close();
      if (eventDelete.type == Event::MouseButtonPressed && eventDelete.mouseButton.button == Mouse::Left)
      {
        if (posDelete.y >= 150 && posDelete.y <= 185)
          selected = SELECT1;
        if (posDelete.x >= 430 && posDelete.x <= 530 && posDelete.y >= 300 && posDelete.y <= 330)
          selected = SELECTBUTTONOKE;
        if (posDelete.x >= 270 && posDelete.x <= 370 && posDelete.y >= 300 && posDelete.y <= 330)
          selected = SELECTBUTTONEXIT;
      }
      textEnter(eventDelete, id, name, selected); //
      __id.setString(id);
      if (eventDelete.type == Event::TextEntered || eventDelete.type == Event::MouseButtonPressed)
        switch (selected)
        {
        case SELECT1:
          line.setPosition((__id.getPosition().x + __id.getGlobalBounds().width + 5), 154);
          break;
        case SELECTBUTTONOKE:
          selected = SELECT0;
          line.setFillColor(Color::Transparent);
          if (id == "")
          {
            message.setString("Please enter computer id");
            message.setPosition(220, 240);
          }
          else if (ql.listComputer.indexOf(id) == -1)
          {
            message.setString("Computer id do not exist");
            message.setPosition(220, 240);
          }
          else
          {
            bool used = false;
            for (int i = 0; i < ql.listRegister.length(); i++)
            {
              if (id == ql.listRegister.at(i).getIdComputer() && ql.listRegister.at(i).getUnRegisteredAt() == 0)
              {
                used = true;
                break;
              }
            }
            if (!used)
            {
              isValid = true;
              message.setString("Delete successfully");
              message.setPosition(255, 240);
            }
            else
            {
              message.setString("Computer is being used. Can not delete");
              message.setPosition(120, 240);
            }
          }
          break;
        case SELECTBUTTONEXIT:
          deleteWindow.close();
          break;
        default:
          break;
        }
    }
    deleteWindow.clear();
    deleteWindow.draw(bgForm5);
    deleteWindow.draw(__id);
    deleteWindow.draw(line);
    deleteWindow.draw(posX);
    deleteWindow.draw(posY);
    deleteWindow.draw(message);
    deleteWindow.display();
    if (isValid)
    {
      int index = ql.listComputer.indexOf(id);
      ql.listComputer.removeAt(index);
      ql.dbComputer.Delete(index);
      int i = 0;
      while (i < ql.listRegister.length())
      {
        if (ql.listRegister.at(i).getIdComputer() == id)
        {
          ql.listRegister.removeAt(i);
          ql.dbRegister.Delete(i);
        }
        else
          i++;
      }
      clock.restart();
      while (clock.getElapsedTime().asSeconds() <= 1)
        selected = 0;
      deleteWindow.close();
    }
  }
}
void Func6()
{
  Sprite bgFunc6(bgFunc6Texture, IntRect(0, 0, 2000, 1200));
  Text _id("", font);
  _id.setFillColor(vinhColor);
  Text _name("", font);
  _name.setFillColor(vinhColor);
  Text _status("", font);
  _status.setFillColor(vinhColor);

  while (window.isOpen())
  {
    Event e;
    Vector2i pos = Mouse::getPosition(window);
    Vector2i posClickedStatus;
    while (window.pollEvent(e))
    {
      int count = 0;
      if (e.type == Event::Closed)
        window.close();
      if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
      {
        if (pos.x >= 0 && pos.x <= 210 && pos.y >= 1130 && pos.y <= 1190)
          Home();
        if (pos.x >= 1500 && pos.x <= 1700)
          posClickedStatus = pos;
      }
      window.clear();
      window.draw(bgFunc6);
      for (int i = 0; i < ql.listComputer.length(); i++)
      {
        _id.setString(ql.listComputer.at(i).getId());
        _id.setPosition(330, 230 + 40 * i);
        _name.setString(ql.listComputer.at(i).getName());
        _name.setPosition(820, 230 + 40 * i);
        if (ql.listComputer.at(i).getStatus() == "not_using")
          _status.setString("Not using");
        else
          _status.setString("Using");
        _status.setPosition(1520, 230 + 40 * i);
        if (ql.listComputer.at(i).getStatus() == "using" && posClickedStatus.y >= _status.getPosition().y && posClickedStatus.y <= _status.getPosition().y + _status.getGlobalBounds().height)
        {
          Text posX("", font);
          posX.setFillColor(Color::White);
          posX.setPosition(0, 0);
          Text posY("", font);
          posY.setFillColor(Color::White);
          posY.setPosition(0, 30);
          posClickedStatus.x = 0;
          posClickedStatus.y = 0;
          RenderWindow smallWindow(VideoMode(1500, 460), "Infomation", Style::Titlebar | Style::Close);
          Sprite bgForm6(bgForm6Texture, IntRect(0, 0, 1500, 460));
          string id = ql.listComputer.at(i).getIdStudent();
          Text __id(id, font);
          __id.setFillColor(vinhColor);
          __id.setPosition(185, 210);
          int indexStudent = ql.listStudent.indexOf(id);
          Text __name(ql.listStudent.at(indexStudent).getName(), font);
          __name.setFillColor(vinhColor);
          __name.setPosition(640, 210);
          Text __time("", font);
          for (int j = 0; j < ql.listRegister.length(); j++)
          {
            if (id == ql.listRegister.at(j).getIdStudent() && ql.listRegister.at(j).getUnRegisteredAt() == 0)
            {
              const time_t now = ql.listRegister.at(j).getRegisteredAt();
              tm *ltm = localtime(&now);
              string hour = ltm->tm_hour >= 10 ? to_string(ltm->tm_hour) : "0" + to_string(ltm->tm_hour);
              string min = ltm->tm_min >= 10 ? to_string(ltm->tm_min) : "0" + to_string(ltm->tm_min);
              string sec = ltm->tm_sec >= 10 ? to_string(ltm->tm_sec) : "0" + to_string(ltm->tm_sec);
              string mday = ltm->tm_mday >= 10 ? to_string(ltm->tm_mday) : "0" + to_string(ltm->tm_mday);
              string mon = ltm->tm_mon + 1 >= 10 ? to_string(ltm->tm_mon + 1) : "0" + to_string(ltm->tm_mon + 1);
              string timeRegister = hour + ":" + min + ":" + sec + " " + mday + "/" + mon + "/" + to_string(1900 + ltm->tm_year);
              __time.setString(timeRegister);
              break;
            }
          }
          __time.setFillColor(vinhColor);
          __time.setPosition(1050, 210);
          while (smallWindow.isOpen())
          {
            Vector2i posSmallWindow = Mouse::getPosition(smallWindow);
            Event event;
            posX.setString(to_string(posSmallWindow.x));
            posY.setString(to_string(posSmallWindow.y));
            while (smallWindow.pollEvent(event))
            {
              if (event.type == Event::Closed)
                smallWindow.close();
              if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
              {
                if (posSmallWindow.x >= 570 && posSmallWindow.x <= 805 && posSmallWindow.y >= 340 && posSmallWindow.y <= 410)
                  smallWindow.close();
              }
            }
            smallWindow.clear();
            smallWindow.draw(bgForm6);
            smallWindow.draw(posX);
            smallWindow.draw(posY);
            smallWindow.draw(__id);
            smallWindow.draw(__name);
            smallWindow.draw(__time);
            smallWindow.display();
          }
        }
        window.draw(_id);
        window.draw(_name);
        window.draw(_status);
      }
      window.display();
    }
  }
}
void Func7()
{
  Sprite bgFunc7(bgFunc7Texture, IntRect(0, 0, 2000, 1200));
  Text _id("", font);
  _id.setFillColor(vinhColor);
  Text _name("", font);
  _name.setFillColor(vinhColor);
  Text _totalTime("", font);
  _totalTime.setFillColor(vinhColor);
  while (window.isOpen())
  {
    Event event7;
    Vector2i pos = Mouse::getPosition(window);
    while (window.pollEvent(event7))
    {
      int count = 0;
      if (event7.type == Event::Closed)
        window.close();
      if (event7.type == Event::MouseButtonPressed && event7.mouseButton.button == Mouse::Left)
      {
        if (pos.x >= 0 && pos.x <= 210 && pos.y >= 1130 && pos.y <= 1190)
          Home();
      }
      window.clear();
      window.draw(bgFunc7);
      for (int i = 0; i < ql.listComputer.length(); i++)
      {
        _id.setString(ql.listComputer.at(i).getId());
        _id.setPosition(320, 230 + 40 * i);
        _name.setString(ql.listComputer.at(i).getName());
        _name.setPosition(815, 230 + 40 * i);
        _totalTime.setString(to_string(ql.listComputer.at(i).getTimeUsed()));
        _totalTime.setPosition(1470, 230 + 40 * i);
        window.draw(_id);
        window.draw(_name);
        window.draw(_totalTime);
      }
      window.display();
    }
  }
}
void Form8(string *listId, string *listUserId, string *listUserName, string *listBegin, string *listEnd, int &length)
{
  length = 0;
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  Clock clock;
  int timeRound, timeUp;
  RenderWindow smallWindow(VideoMode(800, 360), "Date time", Style::Titlebar | Style::Close);
  Sprite bgForm8(bgForm8Texture, IntRect(0, 0, 1500, 460));
  string date, fuckingTime;
  Text __date("", font);
  __date.setFillColor(Color::Black);
  __date.setPosition(350, 100);
  Text __time("", font);
  __time.setFillColor(Color::Black);
  __time.setPosition(350, 180);
  Text message("", font);
  message.setFillColor(vinhColor);
  message.setPosition(220, 240);
  RectangleShape line(Vector2f(1.6f, 30.f));
  line.setPosition((__date.getPosition().x + __date.getGlobalBounds().width + 5), 104);
  line.setFillColor(Color::Black);
  int selected = 1;
  bool isValid = false;
  while (smallWindow.isOpen())
  {
    isValid = false;
    Vector2i pos8 = Mouse::getPosition(smallWindow);
    posX.setString(to_string(pos8.x));
    posY.setString(to_string(pos8.y));
    Time elapsed = clock.getElapsedTime();
    timeRound = int((round(elapsed.asSeconds())));
    timeUp = int(ceil(elapsed.asSeconds()));
    if (timeRound == timeUp)
      line.setFillColor(Color::Transparent);
    else
      line.setFillColor(Color::Black);
    if (timeRound > 10000)
      elapsed = clock.restart();
    if (selected == SELECT0)
    {
      line.setFillColor(Color::Transparent);
    }
    Event event;
    while (smallWindow.pollEvent(event))
    {
      if (event.type == Event::Closed)
        smallWindow.close();
      if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
      {
        if (pos8.y >= 100 && pos8.y <= 135)
          selected = SELECT1;
        if (pos8.y >= 180 && pos8.y <= 215)
          selected = SELECT2;
        if (pos8.x >= 430 && pos8.x <= 530 && pos8.y >= 300 && pos8.y <= 330)
          selected = SELECTBUTTONOKE;
        if (pos8.x >= 270 && pos8.x <= 370 && pos8.y >= 300 && pos8.y <= 330)
          selected = SELECTBUTTONEXIT;
      }
      textEnter(event, date, fuckingTime, selected);
      __date.setString(date);
      __time.setString(fuckingTime);
      if (event.type == Event::TextEntered || event.type == Event::MouseButtonPressed)
        switch (selected)
        {
        case SELECT1:
          line.setPosition((__date.getPosition().x + __date.getGlobalBounds().width + 5), 104);
          break;
        case SELECT2:
          line.setPosition((__time.getPosition().x + __time.getGlobalBounds().width + 5), 184);
          break;
        case SELECTBUTTONOKE:
          selected = SELECT0;
          line.setFillColor(Color::Transparent);
          if (date == "")
          {
            message.setString("Please enter date");
            message.setPosition(270, 240);
          }
          // else if (ql.listComputer.indexOf(id) == -1 && name == "")
          // {

          // }
          else
          {
            isValid = true;
          }
          break;
        case SELECTBUTTONEXIT:
          smallWindow.close();
          break;
        default:
          break;
        }
    }
    smallWindow.clear();
    smallWindow.draw(bgForm8);
    smallWindow.draw(__date);
    smallWindow.draw(__time);
    smallWindow.draw(line);
    smallWindow.draw(posX);
    smallWindow.draw(posY);
    smallWindow.draw(message);
    smallWindow.display();
    if (isValid)
    {
      time_t now = time(0);
      tm *ltm = localtime(&now);
      int count = 0;
      string day = "", mon = "", year = "", hour = "", min = "", sec = "";
      while (!date.empty())
      {
        if (date[0] == '/')
        {
          count++;
          date.erase(date.begin());
          continue;
        }
        if (count == 0)
        {
          day += date[0];
          date.erase(date.begin());
        }
        if (count == 1)
        {
          mon += date[0];
          date.erase(date.begin());
        }
        if (count == 2)
        {
          year += date[0];
          date.erase(date.begin());
        }
      }
      count = 0;
      while (!fuckingTime.empty())
      {
        if (fuckingTime[0] == ':')
        {
          count++;
          fuckingTime.erase(fuckingTime.begin());
          continue;
        }
        if (count == 0)
        {
          hour += fuckingTime[0];
          fuckingTime.erase(fuckingTime.begin());
        }
        if (count == 1)
        {
          min += fuckingTime[0];
          fuckingTime.erase(fuckingTime.begin());
        }
        if (count == 2)
        {
          sec += fuckingTime[0];
          fuckingTime.erase(fuckingTime.begin());
        }
      }
      ltm->tm_mday = atoi(day.c_str());
      if (mon != "")
        ltm->tm_mon = atoi(mon.c_str()) - 1;
      if (year != "")
        ltm->tm_year = atoi(year.c_str()) - 1900;
      if (hour != "")
        ltm->tm_hour = atoi(hour.c_str());
      if (min != "")
        ltm->tm_min = atoi(min.c_str());
      if (sec != "")
        ltm->tm_sec = atoi(sec.c_str());
      time_t begin, end;
      if (count == 0 && hour == "")
      {
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
      if (count == 0 && hour != "")
      {
        ltm->tm_min = 0;
        ltm->tm_sec = 0;
        begin = mktime(ltm);
        ltm->tm_min = 59;
        ltm->tm_sec = 59;
        end = mktime(ltm);
      }
      if (count == 1)
      {
        ltm->tm_sec = 0;
        begin = mktime(ltm);
        ltm->tm_sec = 59;
        end = mktime(ltm);
      }
      if (count == 2)
      {
        begin = mktime(ltm);
        end = begin;
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
          long long timeStart = ql.listRegister.at(i).getRegisteredAt();
          long long timeFinish = ql.listRegister.at(i).getUnRegisteredAt();
          tm *ltmBegin = localtime(&timeStart);
          listId[length] = ql.listRegister.at(i).getIdComputer();
          listUserId[length] = ql.listRegister.at(i).getIdStudent();
          listUserName[length] = ql.listStudent.at(ql.listStudent.indexOf(listUserId[length])).getName();
          string hour = ltmBegin->tm_hour >= 10 ? to_string(ltmBegin->tm_hour) : "0" + to_string(ltmBegin->tm_hour);
          string min = ltmBegin->tm_min >= 10 ? to_string(ltmBegin->tm_min) : "0" + to_string(ltmBegin->tm_min);
          string sec = ltmBegin->tm_sec >= 10 ? to_string(ltmBegin->tm_sec) : "0" + to_string(ltmBegin->tm_sec);
          string mday = ltmBegin->tm_mday >= 10 ? to_string(ltmBegin->tm_mday) : "0" + to_string(ltmBegin->tm_mday);
          string mon = ltmBegin->tm_mon + 1 >= 10 ? to_string(ltmBegin->tm_mon + 1) : "0" + to_string(ltmBegin->tm_mon + 1);
          string timeRegister = hour + ":" + min + ":" + sec + " " + mday + "/" + mon + "/" + to_string(1900 + ltmBegin->tm_year);
          listBegin[length] = timeRegister;
          if (timeFinish != 0)
          {
            tm *ltmEnd = localtime(&timeFinish);
            hour = ltmEnd->tm_hour >= 10 ? to_string(ltmEnd->tm_hour) : "0" + to_string(ltmEnd->tm_hour);
            min = ltmEnd->tm_min >= 10 ? to_string(ltmEnd->tm_min) : "0" + to_string(ltmEnd->tm_min);
            sec = ltmEnd->tm_sec >= 10 ? to_string(ltmEnd->tm_sec) : "0" + to_string(ltmEnd->tm_sec);
            mday = ltmEnd->tm_mday >= 10 ? to_string(ltmEnd->tm_mday) : "0" + to_string(ltmEnd->tm_mday);
            mon = ltmEnd->tm_mon + 1 >= 10 ? to_string(ltmEnd->tm_mon + 1) : "0" + to_string(ltmEnd->tm_mon + 1);
            timeRegister = hour + ":" + min + ":" + sec + " " + mday + "/" + mon + "/" + to_string(1900 + ltmEnd->tm_year);
            listEnd[length] = timeRegister;
          }
          length++;
        }
      }
      smallWindow.close();
    }
  }
}
void Func8()
{
  Sprite bgFunc8(bgFunc8Texture, IntRect(0, 0, 2000, 1200));
  string id, userId, name, begin, end;
  Text _id("", font);
  _id.setFillColor(vinhColor);
  Text _userId("", font);
  _userId.setFillColor(vinhColor);
  Text _name("", font);
  _name.setFillColor(vinhColor);
  Text _begin("", font);
  _begin.setFillColor(vinhColor);
  Text _end("", font);
  _end.setFillColor(vinhColor);
  Text message("No data", font);
  message.setFillColor(vinhColor);
  message.setPosition(920, 500);
  Text posX("", font);
  posX.setFillColor(Color::White);
  posX.setPosition(0, 0);
  Text posY("", font);
  posY.setFillColor(Color::White);
  posY.setPosition(0, 30);
  bool isHasResult = false;
  string listId[1000], listUserId[1000], listUserName[1000], listBegin[1000], listEnd[1000];
  int length;
  while (window.isOpen())
  {
    Event e;
    Vector2i pos = Mouse::getPosition(window);
    posX.setString(to_string(pos.x));
    posY.setString(to_string(pos.y));
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
      if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
      {
        if (pos.x >= 0 && pos.x <= 210 && pos.y >= 1130 && pos.y <= 1190)
          Home();
        if (pos.x >= 1560 && pos.x <= 2000 && pos.y >= 1130 && pos.y <= 1190)
        {
          for (int i = 0; i < length; i++)
          {
            listId[i] = "";
            listUserId[i] = "";
            listUserName[i] = "";
            listBegin[i] = "";
            listEnd[i] = "";
          }
          Form8(listId, listUserId, listUserName, listBegin, listEnd, length);
        }
      }
      window.clear();
      window.draw(bgFunc8);
      window.draw(posX);
      window.draw(posY);
      for (int i = 0; i < length; i++)
      {
        _id.setString(listId[i]);
        _id.setPosition(120, 230 + 40 * i);
        _userId.setString(listUserId[i]);
        _userId.setPosition(350, 230 + 40 * i);
        _name.setString(listUserName[i]);
        _name.setPosition(750, 230 + 40 * i);
        _begin.setString(listBegin[i]);
        _begin.setPosition(1155, 230 + 40 * i);
        _end.setString(listEnd[i]);
        _end.setPosition(1600, 230 + 40 * i);
        window.draw(_id);
        window.draw(_userId);
        window.draw(_name);
        window.draw(_begin);
        window.draw(_end);
      }
      if (length == 0)
      {
        window.draw(message);
      }
      window.display();
    }
  }
}
void Exit()
{
  window.close();
}

void Home()
{
  Sprite bgHome(bgHomeTexture, IntRect(0, 0, 2000, 1200));
  Vector2i mousePos;
  while (window.isOpen())
  {
    Event e;
    mousePos = Mouse::getPosition(window);
    while (window.pollEvent(e))
    {
      if (e.type == Event::Closed)
        window.close();
      if (e.type == Event::MouseButtonPressed && e.mouseButton.button == Mouse::Left)
      {
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y >= 200 && mousePos.y <= 285)
        {
          Func1();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y >= 310 && mousePos.y <= 390)
        {
          Func2();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 490 && mousePos.y >= 415)
        {
          Func3();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 595 && mousePos.y >= 515)
        {
          Func4();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 700 && mousePos.y >= 615)
        {
          Func5();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 800 && mousePos.y >= 725)
        {
          Func6();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 907 && mousePos.y >= 822)
        {
          Func7();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 1015 && mousePos.y >= 930)
        {
          Func8();
        }
        if (mousePos.x >= 280 && mousePos.x <= 1720 && mousePos.y <= 1117 && mousePos.y >= 1032)
        {
          Exit();
        }
      }
    }
    window.clear();
    window.draw(bgHome);
    window.display();
  }
}

int main()
{
  loadAssets();
  Home();
  return 0;
}