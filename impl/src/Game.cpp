#include "Game.hpp"

namespace SDLGame
{
    void Game::loadmedia(renderer_ptr renderer)
    {
        SDLTexture::Texture board ("../../impl/assets/board_test.png", renderer);
        textures_.insert({"board", board});

        std::vector <SDLTexture::Texture> bf_textures;
        std::vector <SDLFeature::Feature> bfs;
        for (size_t i = 0; i < 15; ++i) {
            bf_textures.push_back({"../../impl/assets/black_feature.png", renderer});

            bfs.push_back({bf_textures[i], SDLFeature::BLACK});

            field_.push(bfs[i], 12);
        }

        std::vector <SDLTexture::Texture> wf_textures;
        std::vector <SDLFeature::Feature> wfs;
        for (size_t i = 0; i < 15; ++i) {
            wf_textures.push_back({"../../impl/assets/white_feature.png", renderer});

            wfs.push_back({wf_textures[i], SDLFeature::WHITE});

            field_.push(wfs[i], 11);
        }
    }

    void Game::draw_texture(const std::string& id)
    {
        get_texture(id).draw();
    }

    void Game::draw()
    {
        draw_texture("board");
        draw_field();
    }
}