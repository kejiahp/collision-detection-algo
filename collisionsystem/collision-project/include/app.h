#ifndef APP_H
#define APP_H

/**
 * @brief Base application class providing a simple rendering and update loop.
 *
 * This class defines the core interface for applications that perform
 * graphics initialization, rendering, resizing, and per‑frame updates.
 * Derived classes are expected to override the virtual methods to implement
 * custom behavior.
 */
class Application
{
protected:
    /**
     * @brief Current height of the application window.
     */
    int height;

    /**
     * @brief Current width of the application window.
     */
    int width;

    /**
     * @brief Time interval between simulation updates.
     *
     * Typically represents the fixed timestep used for physics or animation.
     */
    float timeinterval;

    /**
     * @brief A numeric range value used by the application.
     *
     * The purpose of this value depends on the specific application
     * implementation (e.g., coordinate scaling, simulation bounds).
     */
    float nRange;

public:
    /**
     * @brief Initializes graphics resources and rendering state.
     *
     * Called once at startup. Derived classes should override this method
     * to set up OpenGL/DirectX resources, load textures, or configure
     * rendering parameters.
     */
    virtual void initGraphics();

    /**
     * @brief Renders the current frame.
     *
     * Called every frame after update(). Derived classes should override
     * this method to draw the scene.
     */
    virtual void display();

    /**
     * @brief Handles window resizing events.
     *
     * @param width New width of the window.
     * @param height New height of the window.
     */
    virtual void resize(int width, int height);

    /**
     * @brief Updates the application state.
     *
     * Called once per frame before display(). Derived classes should override
     * this method to update physics, animations, or other time‑dependent logic.
     */
    virtual void update();

    /**
     * @brief Retrieves the current simulation time interval.
     *
     * @return The time interval value.
     */
    float getTimeinterval();

    /**
     * @brief Sets the simulation time interval.
     *
     * @param timeint New time interval value.
     */
    void setTimeinterval(float timeint);

    /**
     * @brief Gets the current window height.
     *
     * @return The height value.
     */
    int getheight();

    /**
     * @brief Gets the current window width.
     *
     * @return The width value.
     */
    int getwidth();
};


#endif // APP_H