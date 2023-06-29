#pragma once
#include <string>
#include <memory>
#include <vector>
using namespace std;
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
class Character;
using CharacterPtr = std::shared_ptr<Character>;
	class Character
	{
		protected:
			Character(const Character&) = default;
			Character() = default;
			Character& operator=(const Character& ) = default;
		public:				
			virtual float CalcDamage() = 0;
			virtual void Attack(Character& otherHero) = 0;
			virtual void takeDamage(Character& otherHero) = 0;
			virtual CharacterPtr clone() const = 0;			
			virtual void ability() = 0;
			virtual ~Character() = default;
			virtual bool equals(CharacterPtr other) const = 0;

			virtual  float get_health() const = 0;
			virtual  float get_armor() const = 0;
			virtual  float get_damage() const = 0;
			virtual  std::string get_name()const = 0;

			virtual int get_abilityChance() const = 0;
			virtual bool get_abylity_proc() const = 0;
			virtual float get_normal_damage() const = 0;
			virtual float get_normal_armor() const = 0;
	};
//-------------------------------------------------------------------------------------------
	class Knight : public Character
	{
		private:
			float health;
			float armor;
			float damage;
			float normal_health;
			float normal_armor;
			float normal_damage;
			int abilityChance = 15;
			bool pass_abylity_proc = 0;
			std::string name;
		public:
			Knight(float normal_health, float normal_armor, float normal_damage, string name);
			float get_health() const override;
			float get_armor() const override;
			float get_damage() const override;
			std::string get_name()const override;
			int get_abilityChance() const override;
			bool get_abylity_proc() const override;
			float get_normal_damage() const override;
			float get_normal_armor() const override;

			void set_health(float _health);
			void set_armor(float _armor);
			void set_damage(float _damage);
			void set_name(std::string _name);
			float CalcDamage() override;
			void Attack(Character& otherHero) override;
			void takeDamage(Character& otherHero) override;
			CharacterPtr clone() const override;
			void ability() override;
			bool equals(CharacterPtr other) const override;
	};
//-------------------------------------------------------------------------------------------
class Assasin : public Character
	{
	private:
		float health;
		float armor;
		float damage;
		float normal_health;
		float normal_armor;
		float normal_damage;
		int abilityChance = 25;
		bool pass_abylity_proc = 0;
		bool dodge = 0;
		std::string name;
	public:
		Assasin(float normal_health, float normal_armor, float normal_damage, string name);
		float get_health() const override;
		float get_armor() const override;
		float get_damage() const override;
		std::string get_name()const override;
		int get_abilityChance() const override;
		bool get_abylity_proc() const override;
		float get_normal_damage() const override;
		float get_normal_armor() const override;

		void set_health(float _health);
		void set_armor(float _armor);
		void set_damage(float _damage);
		void set_name(std::string _name);

		float CalcDamage() override;
		void Attack(Character & otherHero) override;
		void takeDamage(Character & otherHero) override;
		CharacterPtr clone() const override;
		void ability() override;
		bool equals(CharacterPtr other) const override;
	};
//-------------------------------------------------------------------------------------------
class Berserk : public Character
{
private:
	float health;
	float armor;
	float damage;
	float normal_health;
	float normal_armor;
	float normal_damage;
	int abilityChance = 15;
	bool pass_abylity_proc = 0;
	float abylity_scale = 1;
	std::string name;
public:
	Berserk(float normal_health, float normal_armor, float normal_damage, string name);
	float get_health() const override;
	float get_armor() const override;
	float get_damage() const override;
	std::string get_name()const override;
	int get_abilityChance() const override;
	bool get_abylity_proc() const override;
	float get_normal_damage() const override;
	float get_normal_armor() const override;


	void set_health(float _health);
	void set_armor(float _armor);
	void set_damage(float _damage);
	void set_name(std::string _name); 

	float CalcDamage() override;
	void Attack(Character& otherHero) override;
	void takeDamage(Character& otherHero) override;
	CharacterPtr clone() const override;
	void ability() override;
	bool equals(CharacterPtr other) const override;
};
//-------------------------------------------------------------------------------------------
	class CharacterList 
	{
		private:
			std::vector<CharacterPtr> _characters;
		public:
			CharacterList() = default;
			CharacterList(const CharacterList& _characters);
			CharacterList& operator=(const CharacterList& rhs);
			int size() const;

			CharacterPtr operator[](int index) const;


			void insert(CharacterPtr hero);
			void insert(CharacterPtr hero,int index);
			void remove(int index);
			void swap(CharacterList& hero);
					
	};
	int index_of_strongest_hero(const CharacterList& characters);
}
//-------------------------------------------------------------------------------------------




			