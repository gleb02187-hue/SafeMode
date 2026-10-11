#include <Geode/Geode.hpp>
#include <Geode/modify/LevelInfoLayer.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

bool g_safeModeActive = false;

class $modify(SafeModeLevelInfo, LevelInfoLayer) {
    bool init(GJGameLevel* level, bool challenge) {
        if (!LevelInfoLayer::init(level, challenge)) return false;

        auto btnSprite = ButtonSprite::create("SafeMode");
        btnSprite->setScale(0.8f);
        if (g_safeModeActive) {
            btnSprite->setColor({255, 100, 100});
        }

        auto btn = CCMenuItemSpriteExtra::create(
            btnSprite,
            this,
            menu_selector(SafeModeLevelInfo::onSafeMode)
        );
        btn->setID("safemode-btn"_spr);

        auto practiceMenu = this->getChildByIDRecursive("practice-menu");

        if (practiceMenu) {
            auto menu = practiceMenu->getParent();
            if (menu) {
                menu->addChild(btn);
                btn->setPosition(practiceMenu->getPositionX() + 80, practiceMenu->getPositionY());
            }
        } else {
            auto myMenu = CCMenu::create();
            myMenu->addChild(btn);
            this->addChild(myMenu);
            myMenu->setPosition({100, 100});
        }

        return true;
    }

    void onSafeMode(CCObject* sender) {
        g_safeModeActive = !g_safeModeActive;

        if (auto btn = typeinfo_cast<CCMenuItemSpriteExtra*>(sender)) {
            if (auto sprite = typeinfo_cast<ButtonSprite*>(btn->getChildren()->objectAtIndex(0))) {
                sprite->setColor(g_safeModeActive ? ccColor3B{255, 100, 100} : ccColor3B{255, 255, 255});
            }
        }

        FLAlertLayer::create(
            "SafeMode",
            g_safeModeActive ? "ON" : "OFF",
            "OK"
        )->show();
    }
};

class $modify(SafeModePlayLayer, PlayLayer) {
    struct Fields {
        bool m_cheated = false;
    };

    bool init(GJGameLevel* level, bool useReplay, bool dontCreateObjects) {
        if (!PlayLayer::init(level, useReplay, dontCreateObjects)) return false;
        m_fields->m_cheated = false;
        return true;
    }

    void levelComplete() {
        if (g_safeModeActive && m_fields->m_cheated) {
            FLAlertLayer::create(
                "SafeMode",
                "Cheats detected. Level not completed.",
                "OK"
            )->show();
            return;
        }
        PlayLayer::levelComplete();
    }
};
