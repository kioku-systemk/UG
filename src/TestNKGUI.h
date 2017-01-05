

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#include "../third_party/nuklear/nuklear.h"
#include "../third_party/nuklear/demo/glfw_opengl3/nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

class TestNKGUI
{
private:
	struct nk_context* m_ctx;
	GLFWwindow* m_win;
	struct nk_color m_background;

public:
	TestNKGUI(GLFWwindow* win)
	{
		m_win = win;
		m_ctx = initGUI(win);
	}

	~TestNKGUI()
	{
	}

	void Draw()
	{
		makeGUI(m_ctx);
		drawGUI(m_win, m_ctx);
	}

private:

	struct nk_context* initGUI(GLFWwindow* window)
	{
		struct nk_context* ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS);
		{struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		/*struct nk_font *droid = nk_font_atlas_add_from_file(atlas, "../../../extra_font/DroidSans.ttf", 14, 0);*/
		/*struct nk_font *roboto = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Roboto-Regular.ttf", 14, 0);*/
		/*struct nk_font *future = nk_font_atlas_add_from_file(atlas, "../../../extra_font/kenvector_future_thin.ttf", 13, 0);*/
		/*struct nk_font *clean = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyClean.ttf", 12, 0);*/
		/*struct nk_font *tiny = nk_font_atlas_add_from_file(atlas, "../../../extra_font/ProggyTiny.ttf", 10, 0);*/
		/*struct nk_font *cousine = nk_font_atlas_add_from_file(atlas, "../../../extra_font/Cousine-Regular.ttf", 13, 0);*/
		nk_glfw3_font_stash_end();
		/*nk_style_set_font(ctx, &droid->handle);*/}

		return ctx;
	}

	void makeGUI(struct nk_context *ctx)
	{
		/* GUI */
		nk_glfw3_new_frame();
		{struct nk_panel layout;
		if (nk_begin(ctx, &layout, "Demo", nk_rect(50, 50, 230, 250),
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
			NK_WINDOW_MINIMIZABLE | NK_WINDOW_TITLE))
		{
			enum { EASY, HARD };
			static int op = EASY;
			static int property = 20;
			nk_layout_row_static(ctx, 30, 80, 1);
			if (nk_button_label(ctx, "button", NK_BUTTON_DEFAULT))
				fprintf(stdout, "button pressed\n");

			nk_layout_row_dynamic(ctx, 30, 2);
			if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
			if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;

			nk_layout_row_dynamic(ctx, 25, 1);
			nk_property_int(ctx, "Compression:", 0, &property, 100, 10, 1);

			{struct nk_panel combo;
			nk_layout_row_dynamic(ctx, 20, 1);
			nk_label(ctx, "background:", NK_TEXT_LEFT);
			nk_layout_row_dynamic(ctx, 25, 1);
			if (nk_combo_begin_color(ctx, &combo, m_background, 400)) {
				nk_layout_row_dynamic(ctx, 120, 1);
				m_background = nk_color_picker(ctx, m_background, NK_RGBA);
				nk_layout_row_dynamic(ctx, 25, 1);
				m_background.r = (nk_byte)nk_propertyi(ctx, "#R:", 0, m_background.r, 255, 1, 1);
				m_background.g = (nk_byte)nk_propertyi(ctx, "#G:", 0, m_background.g, 255, 1, 1);
				m_background.b = (nk_byte)nk_propertyi(ctx, "#B:", 0, m_background.b, 255, 1, 1);
				m_background.a = (nk_byte)nk_propertyi(ctx, "#A:", 0, m_background.a, 255, 1, 1);
				nk_combo_end(ctx);
			}}
		}
		nk_end(ctx); }
	}


	void drawGUI(GLFWwindow* window, struct nk_context *ctx)
	{
		
		/* Draw */
		{float bg[4];
		int width, height;
		nk_color_fv(bg, m_background);
		glfwGetWindowSize(window, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_DEPTH_BUFFER_BIT);
		/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
		* with blending, scissor, face culling, depth test and viewport and
		* defaults everything back into a default state.
		* Make sure to either a.) save and restore or b.) reset your own state after
		* rendering the UI. */
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		}
	}
};
