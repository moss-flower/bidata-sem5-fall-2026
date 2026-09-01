pub mod gl {
    include!(concat!(env!("OUT_DIR"), "/bindings.rs"));
}

use gl::types::*;
use sfml::graphics::*;
use sfml::system::*;
use sfml::window::*;

use nalgebra_glm as glm;

fn main() {
    let mut window = RenderWindow::new(
        (800, 600),
        "SFML VertexArray accessors Example",
        Style::CLOSE,
        &Default::default(),
    )
    .unwrap();
    window.set_vertical_sync_enabled(true);

    window.clear(Color::BLACK);
    window.display();
}
