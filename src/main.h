#pragma once
#include <Ultralight/Ultralight.h>
#include <AppCore/AppCore.h>

class BasicApp final : public ultralight::AppListener,
                       public ultralight::WindowListener,
                       public ultralight::LoadListener,
                       public ultralight::ViewListener {
public:
    BasicApp();

    ~BasicApp() = default;

    void Run() const;

    void OnUpdate() override;

    void OnClose(ultralight::Window* window) override;

    void OnResize(ultralight::Window* window, uint32_t width, uint32_t height) override;

    void OnFinishLoading(ultralight::View* caller,
                                 uint64_t frame_id,
                                 bool is_main_frame,
                                 const ultralight::String& url) override;

    void OnDOMReady(ultralight::View* caller,
                            uint64_t frame_id,
                            bool is_main_frame,
                            const ultralight::String& url) override;

    void OnChangeCursor(ultralight::View* caller,
      ultralight::Cursor cursor) override;

    void OnChangeTitle(ultralight::View* caller,
      const ultralight::String& title) override;

private:
    ultralight::RefPtr<ultralight::App> _app;
    ultralight::RefPtr<ultralight::Window> _window;
    ultralight::RefPtr<ultralight::Overlay> _overlay;
};