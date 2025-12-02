#include "main.h"
#include "util/path.h"
#include "util/logger.h"

BasicApp::BasicApp() {
    /* Set the logger */
    ultralight::Platform::instance().set_logger(
        ultralight::GetDefaultLogger(Path::ULTRALIGHT_LOG.c_str())
    );
    INFO_LOG("Ultralight log file: %s", Path::ULTRALIGHT_LOG.c_str());

    /* Set the settings */
    ultralight::Settings settings;
    settings.force_cpu_renderer = false;
    settings.developer_name = "Evilur";
    settings.app_name = "Echo";

    /* Set the config */
    ultralight::Config config;
    config.cache_path = Path::LOG_DIR.c_str();

    /* Create a main app instance */
    _app = ultralight::App::Create(settings, config);

    /* Create a window */
    _window = ultralight::Window::Create(_app->main_monitor(), 1280, 720, false,
                                         ultralight::kWindowFlags_Borderless |
                                         ultralight::kWindowFlags_Resizable |
                                         ultralight::kWindowFlags_Titled);

    /* Set the window title */
    _window->SetTitle("Echo");

    /* Create an HTML overlay */
    _overlay = ultralight::Overlay::Create(_window,
                                           _window->width(), _window->height(),
                                           0, 0);

    /* Load a page into the overlay's view */
    _overlay->view()->LoadURL("file:///index.html");

    /* Set listeners */
    _app->set_listener(this);
    _window->set_listener(this);
    _overlay->view()->set_load_listener(this);
    _overlay->view()->set_view_listener(this);
}

void BasicApp::Run() const { _app->Run(); }

void BasicApp::OnUpdate() { }

void BasicApp::OnClose(ultralight::Window* window) {
    _app->Quit();
}

void BasicApp::OnResize(ultralight::Window* window,
                        const uint32_t width, const uint32_t height) {
    _overlay->Resize(width, height);
}

void BasicApp::OnFinishLoading(ultralight::View* caller,
                               uint64_t frame_id,
                               bool is_main_frame,
                               const ultralight::String& url) { }

void BasicApp::OnDOMReady(ultralight::View* caller,
                          uint64_t frame_id,
                          bool is_main_frame,
                          const ultralight::String& url) { }

void BasicApp::OnChangeCursor(ultralight::View* caller,
                              const ultralight::Cursor cursor) {
    _window->SetCursor(cursor);
}

void BasicApp::OnChangeTitle(ultralight::View* caller,
                             const ultralight::String& title) {
    _window->SetTitle(title.utf8().data());
}

int main() {
    /* Init static classes */
    Path::Init();

    /* Run the basic application */
    const BasicApp app;
    app.Run();
    return 0;
}