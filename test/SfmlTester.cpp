#include <SfmlTester.hpp>
#include <ResourceStorage.hpp>

SfmlTester::SfmlTester() : Tester() { }


std::pair<int, int> SfmlTester::runTest() {
  char window_display_check = 'y';
  const std::string& base_path = "C:/Users/jonne/Documents/OOPC/AxesAndTrolls/";
  /* Test 1 */

  std::cout << "## LOAD TEST ##" << std::endl;
  
  ResourceStorage storage = ResourceStorage();

  /* Tests whether or not ResourceStorage and sf::Font's work together as wanted. */
  sf::Text text = loadText("Close the window by clicking x!", storage, base_path + "resources/fonts/TTF/Crimson-Italic.ttf", 50);

  if (text.getFont() != nullptr) {
    addSuccessful("Font Loading");
  } else {
    addUnsuccessful("Font Loading");
  }
  // Record result
  if (storage.getFonts().size() == 0) {
    addUnsuccessful("Font Storing");
  } else {
    addSuccessful("Font Storing");
  }

  /* Tests whether or not ResourceStorage and sf::Sprite's work together as wanted. */
  sf::Sprite background = loadSprite(storage, base_path + "resources/pics/GameLogo.png");
  if (background.getTexture() != nullptr) {
    addSuccessful("Sprite Loading");
  } else {
    addUnsuccessful("Sprite Loading");
  }

  /* Tests the storing */
  if (storage.getTextures().size() == 0) {
    addUnsuccessful("Sprite Storing");
  } else {
    addSuccessful("Sprite & Storing");
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

    if (background.getTexture() != nullptr) {
      window.draw(background);
    }
    if (text.getFont() != nullptr) {
      window.draw(text);
    }

    window.display();
  }

  std::cout << "Did you see a window with text and the game logo? [y]/n ";
  std::cin >> window_display_check;

  window_display_check == 'y' ? addSuccessful("Window Display Test") : addUnsuccessful("Window Display Test");

  return test_results_;
}