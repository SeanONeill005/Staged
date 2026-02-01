// TextureManager.h
#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>
#include <variant>
#include <vector>
#include <thread>
#include <mutex>
#include <future>

namespace Textures {
    enum class Stage {
        LeftCurtain,
        RightCurtain,
        LeftLight,
        RightLight
    };

    enum class Props {
        Ball,
        Cactus,
        Chest,
        Popcorn,
        Target,
        Mannequin,
        Gun
    };

    enum class Backgrounds {
        Circus,
        Theatre,
        Western
    };

    enum class Clown {
        Juggle1,
        Juggle2,
        Mask,
        Pose1,
        Pose2
    };

    enum class Cowboy {
        Mask,
        Pose1,
        Pose2,
        Shoot
    };

    enum class UI {
        PlayButton,
        QuitButton,
        HitMarker
    };
}

using TextureID = std::variant<
    Textures::Props,
    Textures::Backgrounds,
    Textures::Clown,
    Textures::Cowboy,
    Textures::UI,
    Textures::Stage
>;

// Hash support for variant in unordered_map
namespace std {
    template<>
    struct hash<TextureID> {
        size_t operator()(const TextureID& id) const {
            size_t seed = id.index();
            std::visit([&seed](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;
                seed ^= std::hash<T>{}(arg)+0x9e3779b9 + (seed << 6) + (seed >> 2);
                }, id);
            return seed;
        }
    };
}

class TextureManager {
public:
    // Delete copy constructor and assignment operator
    TextureManager(const TextureManager&) = delete;
    TextureManager& operator=(const TextureManager&) = delete;

    // Get the singleton instance
    static TextureManager& getInstance() {
        static TextureManager instance;
        return instance;
    }

    // Load a texture and associate it with an ID (thread-safe)
    bool load(const TextureID& id, const std::string& filepath) {
        auto texture = std::make_unique<sf::Texture>();

        if (!texture->loadFromFile(filepath)) {
            return false;
        }

        std::lock_guard<std::mutex> lock(mutex_);
        textures_[id] = std::move(texture);
        return true;
    }

    // Convenience method that prepends the assets path
    bool loadFromAssets(const TextureID& id, const std::string& filename) {
        return load(id, "ASSETS\\IMAGES\\" + filename);
    }

    // Queue a texture to be loaded (for batch loading)
    void queueLoad(const TextureID& id, const std::string& filepath) {
        loadQueue_.emplace_back(id, filepath);
    }

    // Queue with assets path
    void queueLoadFromAssets(const TextureID& id, const std::string& filename) {
        queueLoad(id, "ASSETS\\IMAGES\\" + filename);
    }

    // Load all queued textures in parallel
    bool loadQueuedTextures(unsigned int numThreads = 0) {
        if (loadQueue_.empty()) {
            return true;
        }

        // Use hardware concurrency if not specified
        if (numThreads == 0) {
            numThreads = std::thread::hardware_concurrency();
            if (numThreads == 0) numThreads = 4; // Fallback
        }

        std::vector<std::future<bool>> futures;
        std::atomic<size_t> currentIndex(0);
        bool allSucceeded = true;

        // Lambda for worker threads
        auto loadWorker = [this, &currentIndex]() {
            bool localSuccess = true;
            while (true) {
                size_t index = currentIndex.fetch_add(1);
                if (index >= loadQueue_.size()) {
                    break;
                }

                const auto& [id, filepath] = loadQueue_[index];
                if (!load(id, filepath)) {
                    localSuccess = false;
                }
            }
            return localSuccess;
            };

        // Launch worker threads
        for (unsigned int i = 0; i < numThreads; ++i) {
            futures.push_back(std::async(std::launch::async, loadWorker));
        }

        // Wait for all threads and check results
        for (auto& future : futures) {
            if (!future.get()) {
                allSucceeded = false;
            }
        }

        loadQueue_.clear();
        return allSucceeded;
    }

    // Get a texture by ID
    sf::Texture& get(const TextureID& id) {
        std::lock_guard<std::mutex> lock(mutex_);
        return *textures_.at(id);
    }

    // Check if a texture exists
    bool has(const TextureID& id) const {
        std::lock_guard<std::mutex> lock(mutex_);
        return textures_.find(id) != textures_.end();
    }

    // Unload a specific texture
    void unload(const TextureID& id) {
        std::lock_guard<std::mutex> lock(mutex_);
        textures_.erase(id);
    }

    // Clear all textures
    void clear() {
        std::lock_guard<std::mutex> lock(mutex_);
        textures_.clear();
        loadQueue_.clear();
    }

private:
    TextureManager() = default;
    ~TextureManager() = default;

    std::unordered_map<TextureID, std::unique_ptr<sf::Texture>> textures_;
    std::vector<std::pair<TextureID, std::string>> loadQueue_;
    mutable std::mutex mutex_;
};