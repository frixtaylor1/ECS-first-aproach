
#include <cstddef> // Para std::size_t
#include <limits>  // Para std::numeric_limits
#include <memory>
#include <raylib.h>
#include <stdlib.h> // Required for: abs()
#include <vector>

#define interface   struct
#define implements  public
#define extends     public

/**
 * Compatible with std::vector
 * Only takes 2 parameters in the template arguments
 *
 *  @param typename - T type
 *  @param size_t   - Capacity
 */
template <typename T, std::size_t Capacity> class StaticAllocator {
public:

  using value_type      = T;
  using pointer         = T *;
  using const_pointer   = const T *;
  using reference       = T &;
  using const_reference = const T &;
  using size_type       = std::size_t;
  using difference_type = std::ptrdiff_t;

  template <typename U> struct rebind {
    using other = StaticAllocator<U, Capacity>;
  };

  StaticAllocator() noexcept {}

  template <typename U>
  StaticAllocator(const StaticAllocator<U, Capacity> &) noexcept {}

  pointer allocate(size_type n) {
    if (n > Capacity) {
      throw std::bad_alloc();
    }
    return reinterpret_cast<pointer>(&storage);
  }

  void deallocate(pointer p, size_type n) noexcept {}

  size_type max_size() const noexcept { return Capacity; }

private:
  alignas(alignof(T)) unsigned char storage[sizeof(T) * Capacity];
};

template<typename T, std::size_t Capacity>
bool operator==(const StaticAllocator<T, Capacity>&, const StaticAllocator<T, Capacity>&) noexcept {
    return true;
}

template<typename T, std::size_t Capacity>
bool operator!=(const StaticAllocator<T, Capacity>&, const StaticAllocator<T, Capacity>&) noexcept {
    return false;
}

  /**
   * Specification of type IComponent...
   */
  interface IComponent{virtual ~IComponent(){}};

  interface IDrawableComponent : extends IComponent{ 
    virtual ~IDrawableComponent(){}
  };

  struct RectangleDrawableComponent : implements IDrawableComponent {
    RectangleDrawableComponent(float posX, float posY, float width, float height, Color color)
      : color(color), rectangle({posX, posY, width, height}) {}

    virtual ~RectangleDrawableComponent() {}
    Color color {
      /* R */0, 
      /* G */0, 
      /* B */0, 
      /* A */0
    };
    Rectangle rectangle { 
      /* POSX */  0.f, 
      /* POSY */  0.f, 
      /* WIDTH */ 0.f, 
      /* HEIGHT */0.f
    };
  };

  struct ImageDrawableComponent : implements IDrawableComponent {
    virtual ~ImageDrawableComponent() {}
    Image image;
  };

  struct TextureDrawableComponent : implements IDrawableComponent {
    virtual ~TextureDrawableComponent() {}
    Texture texture;
  };

  struct IMovableComponent : implements IComponent {
    virtual ~IMovableComponent() {}
    bool moving;
  };

  struct PhysicsComponent : implements IComponent {
    virtual ~PhysicsComponent() {}
    float speed;
  };

  class Entity {
  public:
    Entity() = default;

    template <typename ComponentType> ComponentType *getComponent() const {
      for (const auto &component : m_components) {
        if (auto castedComponent =
                dynamic_cast<ComponentType *>(component.get())) {
          return castedComponent;
        }
      }
      return nullptr;
    }

    template <typename ComponentType, typename... Args>
    void addComponent(Args &&...args) {
      m_components.emplace_back(
          std::make_unique<ComponentType>(std::forward<Args>(args)...));
    }

  private:
    std::vector<std::unique_ptr<IComponent>, StaticAllocator<std::unique_ptr<IComponent>, 5>> m_components;
  };

  class RenderSystem {
  public:
    RenderSystem(std::vector<std::unique_ptr<Entity>>& entities)
      : m_entities(entities) {}

    void render() {
      /*BEGIN DRAWING*/
      BeginDrawing();

        ClearBackground(LIGHTGRAY);
      
        for (auto&& entity : m_entities) {

          if (auto rectangleEntity = entityIsRectangle(entity)) {
            DrawRectangleRec(
              rectangleEntity->rectangle,
              rectangleEntity->color
            );
          }
        }

      EndDrawing();
      /*END DRAWING*/
    }
  protected:
    RectangleDrawableComponent* entityIsRectangle(const std::unique_ptr<Entity>& entity) {
      if (auto rectangle = entity->getComponent<RectangleDrawableComponent>()) {
        return rectangle;
      }
      return nullptr;
    }

  private:
    std::vector<std::unique_ptr<Entity>>& m_entities;
  };

  int main(void) {

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib and ECS example");
      SetTargetFPS(60); 

      std::unique_ptr<Entity> player1 = std::make_unique<Entity>();
      player1->addComponent<RectangleDrawableComponent>(10, GetScreenHeight() / 2.0f - 50, 200, 100, GOLD);    
      
      std::vector<std::unique_ptr<Entity>> entities;
      entities.emplace_back(std::move(player1));

      RenderSystem renderSys(entities);

      while (!WindowShouldClose()) {
        renderSys.render();
      }

    CloseWindow();

    return 0; 
  }