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
			static Character createKnight(float health, float armor, float damage);
			static Character createAssasin(float health, float armor, float damage);
			static Character createBerserk(float health, float armor, float damage);

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

			void ability();
	};
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------
	class CharacterList 
	{
		public:
			static const int CAPACITY = 10;

		private:
			Character _characters[CAPACITY];
			int _size;

		public:
			CharacterList();
			CharacterList(Character _character[], int _size);
			int size() const;

			Character& operator[](int index) ;


			void insert(int index, Character hero);
			void remove(int index);

			int search_strongest() const;
	};


//-------------------------------------------------------------------------------------------
}