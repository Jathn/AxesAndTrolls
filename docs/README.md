# Game Structure README

This README provides an overview of the classes and their relationships in the game structure. The structure includes a variety of classes that handle different aspects of the game, from graphical representation to gameplay mechanics.

## Classes

### Tile
- **Attributes:** Id, terrain type, Units & Building.
- **Description:** Represents a single tile on the game map with specific terrain and may contain units or buildings.

### Units
- **Subclasses:** Hit chance, Cost, Movement.
- **Description:** Represents movable characters or objects within the game. Each unit has attributes like hit chance, cost, and movement capabilities.

### Player
- **Attributes:** Resources, Units & Buildings, Type.
- **Description:** Represents individual players in the game with their resources and owned units & buildings.

### GameStateManager
- **Attributes:** Players & Current Map Phase.
- **Description:** Manages the overall state of the game including current players, map and phase of gameplay.

### GameGraphicManager 
- **Attributes:** PlayerView TileView MouseHandling.
- **Description**: Handles graphical representation for various elements within the game like players and tiles.

### GraphicsOp 
**Subclasses**: Phase RenderWindow GameGraphicsManager MenuGraphicsManager.
**Description**: Operates all graphics-related tasks including rendering windows and managing graphics for both games and menus.

### MenuGraphicsManager 
**Attributes**: RulebookDisplay Button.
**Description**: Manages graphics specifically for menu displays including rulebooks and buttons.

### Button 
**Attributes**: OnClick Visuals.
**Description**: Represents interactive buttons within menus with specific visuals and click actions.

## Relationships

1. `Tile` is associated with `Units` through its attributes which include units. It's also connected to `Player` through Buildings & Units attribute indicating ownership or occupation by a player’s units or buildings.

2. `Player` is linked to `GameStateManager`, indicating that each player’s state is managed within this class which also handles overall gameplay state including phases etc.

3. `GameGraphicManager` is associated with both `Tile` (through TileView) indicating it handles how tiles are graphically represented; it's also linked to ‘Player’ (through PlayerView) handling player-specific graphical elements 

4. ‘GraphicsOp’ encompasses operations related to graphics across phases of gameplay as well as menu displays; it’s linked directly to ‘GameGraphicManager’ for in-game graphics operations as well as ‘MenuGraphicsManager
