#include <SfmlTester.hpp>
#include <ResourceStorage.hpp>

SfmlTester::SfmlTester() : test_results_(std::make_pair<int,int>(0,0)) { }


void SfmlTester::addCompleted(const std::string& str) {
  std::cout << "Test completed: " << str << std::endl;
  test_results_.first += 1;
  test_results_.second += 1;
}


void SfmlTester::addUnsuccessful(const std::string& str) {
  std::cout << "Test unsuccessful: " << str << std::endl;
  test_results_.first += 1;
}


std::pair<int, int> SfmlTester::runTest() {
  char window_display_check = 'y';
  /* Test 1 */

  std::cout << "## LOAD TEST ##" << std::endl;
  
  ResourceStorage storage = ResourceStorage();

  /* Tests whether or not ResourceStorage and sf::Font's work together as wanted. */
  sf::Text text = loadText("Close the window by clicking x!", storage, "../resources/fonts/TTF/Crimson-Italic.ttf", 50);
  // Record result
  if (storage.getFonts().size() == 0) {
    addUnsuccessful("Font Loading");
  } else {
    storage.getFonts()[0] != nullptr ? addCompleted("Font Loading") : addUnsuccessful("Font Loading");
  }

  /* Tests whether or not ResourceStorage and sf::Sprite's work together as wanted. */
  sf::Sprite background = loadSprite(storage, "../resources/pics/GameLogo.png");
  if (storage.getTextures().size() == 0) {
    addUnsuccessful("Font Loading");
  } else {
    storage.getTextures()[0] != nullptr ? addCompleted("Texture Loading") : addUnsuccessful("Font Loading");
  }

  /* End of test 1 */

  /* Test 2 */

  std::cout << "## WINDOW DISPLAY TEST ##" << std::endl;

  /* Creates window */
  sf::RenderWindow window(sf::VideoMode(1920, 1080), "Test Window");

  /* Loop for displaying the window */
  while(window.isOpen()) {

    sf::Event event;

    while(window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }
    
    window.clear();

    window.draw(background);
    window.draw(text);

    window.display();
  }

  std::cout << "Did you see a window with text and the game logo? [y]/n ";
  std::cin >> window_display_check;

  window_display_check == 'y' ? addCompleted("Window Display Test") : addUnsuccessful("Window Display Test");

  return test_results_;
}