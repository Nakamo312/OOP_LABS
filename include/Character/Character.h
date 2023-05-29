#pragma once
#include <string>
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
			float normal_armor;
			float normal_damage;
			int abilityChance;
			float abilityScale;
			bool dodge;
			bool pass_abylity_proc = 0;
			std::string name;

		public:
			Character(Type _type, float health, float armor, float damage, std::string name);
			static CharacterPtr createKnight(float health, float armor, float damage, std::string name);
			static CharacterPtr createAssasin(float health, float armor, float damage, std::string name);
			static CharacterPtr createBerserk(float health, float armor, float damage, std::string name);

			Character();

			float get_health() const;
			Type get_type() const;
			float get_armor() const;
			float get_damage() const;
			std::string get_name()const;
			int get_abilityChance() const;
			bool get_abylity_proc() const;
			float get_normal_damage() const;
			float get_normal_armor() const;

			void set_health(float _health);
			void set_armor(float _armor);
			void set_damage(float _damage);
			void set_name(std::string _name);
			float CalcDamage();
			void Attack(Character& otherHero);
			void takeDamage(Character& otherHero);
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