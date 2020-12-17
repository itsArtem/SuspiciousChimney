#pragma once

namespace sus::states
{
	class GameState
	{
	public:
		virtual ~GameState() = 0;

		virtual void update() noexcept = 0;
		virtual void render() const noexcept = 0;

	protected:
		GameState() = default;
		GameState(const GameState &other) = default;
		GameState(GameState &&other) = default;

		GameState &operator =(const GameState &other) = default;
		GameState &operator =(GameState &&other) = default;
	};
}