#include "cave_cell.h"

bool CaveCell::IsAlive() const { return state_ == CaveCellStates::kAlive; }

bool CaveCell::IsDead() const { return state_ == CaveCellStates::kDead; }

void CaveCell::Die() { state_ = CaveCellStates::kDead; }

void CaveCell::Reborn() { state_ = CaveCellStates::kAlive; }

void CaveCell::Reset() { Die(); }
