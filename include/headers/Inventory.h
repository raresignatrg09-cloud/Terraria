#pragma once

#include <array>
#include "Item.hpp"

struct InventorySlot
{
	Item item;
	int count;

	bool isEmpty() const
	{
		return item.type == ItemType::NONE || count <= 0;
	}

	void clear()
	{
		item = Item{};
		count = 0;
	}
};

class Inventory
{
public:
	static constexpr int MAX_SLOTS = 9;

	InventorySlot& getSlot(int index)
	{
		return slots[index];
	}

	const InventorySlot& getSlot(int index) const
	{
		return slots[index];
	}

	int getSelectedSlotIndex() const
	{
		return selectedSlotIndex;
	}

	InventorySlot& getSelectedSlot()
	{
		return slots[selectedSlotIndex];
	}

	void selectSlot(int index)
	{
		if (index >= 0 && index < MAX_SLOTS)
		{
			selectedSlotIndex = index;
		}
	}


	bool addItem(const Item& item, int count)
	{
		if (count <= 0 || item.type == ItemType::NONE)
			return false;

		// First, fill existing stacks of the same item.
		for (auto& slot : slots)
		{
			if (!slot.isEmpty() &&
				slot.item.type == item.type &&
				slot.count < slot.item.maxStackSize)
			{
				int spaceLeft =
					slot.item.maxStackSize - slot.count;

				int toAdd = std::min(spaceLeft, count);

				slot.count += toAdd;
				count -= toAdd;

				if (count == 0)
					return true;
			}
		}

		// Then, put remaining items into empty slots.
		for (auto& slot : slots)
		{
			if (slot.isEmpty())
			{
				int toAdd = std::min(item.maxStackSize, count);

				slot.item = item;
				slot.count = toAdd;
				count -= toAdd;

				if (count == 0)
					return true;
			}
		}

		return false;
	}


	void removeItem(int index, int count)
	{
		if (index >= 0 && index < MAX_SLOTS)
		{
			auto& slot = slots[index];
			if (!slot.isEmpty())
			{
				slot.count -= count;
				if (slot.count <= 0)
				{
					slot.clear();
				}
			}
		}
	}

private:
	std::array<InventorySlot, MAX_SLOTS> slots;
	int selectedSlotIndex = 0;
};