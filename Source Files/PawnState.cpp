#include "../Headers/PawnState.hpp"

std::ostream& operator<<(std::ostream& os, const PawnState& state) {
    switch (state) {
        case PawnState::idle:
            os << "idle";
            break;
        case PawnState::jump:
            os << "jump";
            break;
        case PawnState::jumpAttack:
            os << "jumpAttack";
            break;
        case PawnState::die:
            os << "die";
            break;
        case PawnState::roll:
            os << "roll";
            break;
        case PawnState::squat:
            os << "squat";
            break;
        case PawnState::happy:
            os << "happy";
            break;
        case PawnState::push:
            os << "push";
            break;
        case PawnState::lift:
            os << "lift";
            break;
        case PawnState::hurt:
            os << "hurt";
            break;
        case PawnState::fly:
            os << "fly";
            break;
        case PawnState::pic:
            os << "pic";
            break;
        case PawnState::run:
            os << "run";
            break;
        case PawnState::directAttack:
            os << "directAttack";
            break;
        case PawnState::directDoubleAttack:
            os << "directDoubleAttack";
            break;
        case PawnState::throwAttack:
            os << "throwAttack";
            break;
        default:
            os << "unknown";
    }
    return os;
}