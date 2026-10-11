#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(SafeModePlayLayer, PlayLayer) {
void levelComplete() {
PlayLayer::levelComplete();
}
};
