#pragma once

namespace character 
{
//-------------------------------------------------------------------------------------------
	enum class Type
	{
		Knight,
		Assasin,
		Berserk
	};


	int const KnightAbilityChance = 15;
	int const AssasinAbilityChance = 25;
	int const BerserkAbilityChance = 15;
	class Character;
	using CharacterPtr = Character*;
//-------------------------------------------------------------------------------------------

 //-------------------------------------------------------------------------------------------
	class Character
	{
		private:
			Type _type;
			float health;
			float armor;
			float damage;
			int abilityChance;
			float abilityScale;
			bool dodge;

		public:
			Character(Type _type, float health, float armor, float damage);
			static CharacterPtr createKnight(float health, float armor, float damage);
			static CharacterPtr createAssasin(float health, float armor, float damage);
			static CharacterPtr createBerserk(float health, float armor, float damage);

			Character();

			float get_health() const;
			Type get_type() const;
			float get_armor() const;
			float get_damage() const;
			int get_abilityChance() const;

			void set_health(float _health);
			void set_armor(float _armor);
			void set_damage(float _damage);

			float CalcDamage() const;
			void Attack(Character& otherHero) const;
			void takeDamage(const Character& otherHero);
			CharacterPtr clone() const;
			CharacterPtr operator=(const Character& rhs);
			void ability();
	};
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
	class CharacterList 
	{
		private:
			CharacterPtr* _characters;
			int _size;

		public:
			CharacterList();
			CharacterList(const CharacterList& _characters);
			CharacterList& operator=(const CharacterList& rhs);
			int size() const;

			CharacterPtr operator[](const int index) const;


			void insert(CharacterPtr hero, int index);
			void insert(CharacterPtr hero);
			void remove(CharacterPtr hero);
			void swap(CharacterList& hero);
			~CharacterList();
			int index_of_strongest_hero() const;

			
	};


//-------------------------------------------------------------------------------------------
}