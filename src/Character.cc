#include <Character/Character.h>
#include <ctime>
#include <stdlib.h>
#include <time.h>
#include <stdexcept>
#include <iostream> 
using namespace character;
using namespace std;



//-------------------------------------------------------------------------------------------
Knight::Knight(float norm_health, float norm_armor, float norm_damage, string _name) :
health(norm_health),
normal_health(norm_health),
armor(norm_armor),
normal_armor(norm_armor),
damage(norm_damage),
normal_damage(norm_damage),
name(_name)
{ 

}


float Knight::get_health() const
{
	return health;
}

float Knight::get_armor() const
{
	return armor;
}

float Knight::get_damage() const
{
	return damage;
}
std::string Knight::get_name() const
{
	return name;
}

int Knight::get_abilityChance() const
{
	return abilityChance;
}
bool Knight::get_abylity_proc() const
{
	return pass_abylity_proc;
}
float Knight::get_normal_damage() const
{
	return normal_damage;
}
float Knight::get_normal_armor() const
{
	return normal_armor;
}
void Knight::set_health(float _health)
{
	health = _health;
}

void Knight::set_name(std:: string _name) 
{
	name = _name;
}
void Knight::set_armor(float _armor)
{
	armor = _armor;
}

void Knight::set_damage(float _damage)
{
	damage = _damage;
}

void Knight::ability()
{
	armor = (1.25f * normal_armor) + 2;
	damage = (0.65f * normal_damage);
}
float Knight::CalcDamage()
{
	return damage;
}
void Knight::Attack(Character& otherHero)
{
	pass_abylity_proc = 0;
	otherHero.takeDamage(*this);
	armor = normal_armor;
	damage = normal_damage;
}
void Knight::takeDamage(Character& otherHero)
{
	pass_abylity_proc = 0;
	int chance = 1 + rand() % 100;
	if (chance <= abilityChance)
	{
		health -= otherHero.CalcDamage() * ((1 - (armor / 100)) / 2);
		pass_abylity_proc = 1;
	}
	else
	{
		health -= otherHero.CalcDamage() * (1 - (armor / 100));
	}
}

CharacterPtr Knight::clone() const
{
	return make_shared<Knight>(health, armor, damage, name);
}
bool Knight::equals(CharacterPtr other) const {
	const auto downcasted_other = dynamic_pointer_cast<Knight>(other);
	if (downcasted_other == nullptr) {
		return false;
	}

	return abilityChance == downcasted_other->abilityChance;
}

//-------------------------------------------------------------------------------------------
Assasin::Assasin(float norm_health, float norm_armor, float norm_damage, string _name):
health(norm_health),
normal_health(norm_health),
armor(norm_armor),
normal_armor(norm_armor),
damage(norm_damage),
normal_damage(norm_damage),
name(_name)
{
	
}


float Assasin::get_health() const
{
	return health;
}

float Assasin::get_armor() const
{
	return armor;
}

float Assasin::get_damage() const
{
	return damage;
}
std::string Assasin::get_name() const
{
	return name;
}

int Assasin::get_abilityChance() const
{
	return abilityChance;
}
bool Assasin::get_abylity_proc() const
{
	return pass_abylity_proc;
}
float Assasin::get_normal_damage() const
{
	return normal_damage;
}
float Assasin::get_normal_armor() const
{
	return normal_armor;
}
void Assasin::set_health(float _health)
{
	health = _health;
}

void Assasin::set_name(std::string _name)
{
	name = _name;
}
void Assasin::set_armor(float _armor)
{
	armor = _armor;
}

void Assasin::set_damage(float _damage)
{
	damage = _damage;
}

void Assasin::ability()
{
	dodge = 1;
}
float Assasin::CalcDamage()
{
	return damage;
}
void Assasin::Attack(Character& otherHero)
{
	dodge = 0;
	pass_abylity_proc = 0;
	otherHero.takeDamage(*this);
	int chance = 1 + rand() % 100;
	if (chance <= abilityChance)
	{
		pass_abylity_proc = 1;
	}
}
void Assasin::takeDamage(Character& otherHero)
{
	if (dodge)
	{

		dodge = 0;
	}
	else
	{
		health -= otherHero.CalcDamage() * (1 - (armor / 100));
	}
}

CharacterPtr Assasin::clone() const
{
	return make_shared<Assasin>(health, armor, damage, name);
}
bool Assasin::equals(CharacterPtr other) const {
	const auto downcasted_other = dynamic_pointer_cast<Assasin>(other);
	if (downcasted_other == nullptr) {
		return false;
	}

	return abilityChance == downcasted_other->abilityChance;
}
//-------------------------------------------------------------------------------------------
Berserk::Berserk(float norm_health, float norm_armor, float norm_damage, string _name):
health(norm_health),
normal_health(norm_health),
armor(norm_armor),
normal_armor(norm_armor),
damage(norm_damage),
normal_damage(norm_damage),
name(_name)
{

}


float Berserk::get_health() const
{
	return health;
}

float Berserk::get_armor() const
{
	return armor;
}

float Berserk::get_damage() const
{
	return damage;
}
std::string Berserk::get_name() const
{
	return name;
}

int Berserk::get_abilityChance() const
{
	return abilityChance;
}
bool Berserk::get_abylity_proc() const
{
	return pass_abylity_proc;
}
float Berserk::get_normal_damage() const
{
	return normal_damage;
}
float Berserk::get_normal_armor() const
{
	return normal_armor;
}
void Berserk::set_health(float _health)
{
	health = _health;
}

void Berserk::set_name(std::string _name)
{
	name = _name;
}
void Berserk::set_armor(float _armor)
{
	armor = _armor;
}

void Berserk::set_damage(float _damage)
{
	damage = _damage;
}

void Berserk::ability()

{
	armor = normal_armor;
	damage = normal_damage;
	pass_abylity_proc = 0;
	armor = (0.5f * armor) + 1;
	damage = (1.5f * damage);
	abylity_scale = 3;
}
float Berserk::CalcDamage()
{
	pass_abylity_proc = 0;
	int chance = 1 + rand() % 100;
	if (chance <= abilityChance * abylity_scale)
	{
		pass_abylity_proc = 1;
		return damage * 3;
	}
	return damage;
}
void Berserk::Attack(Character& otherHero)
{
	pass_abylity_proc = 0;
	otherHero.takeDamage(*this);
	armor = normal_armor;
	damage = normal_damage;
}
void Berserk::takeDamage(Character& otherHero)
{
	health -= otherHero.CalcDamage() * (1 - (armor / 100));
}

CharacterPtr Berserk::clone() const
{
	return make_shared<Berserk>(health, armor, damage, name);
}
bool Berserk::equals(CharacterPtr other) const {
	const auto downcasted_other = dynamic_pointer_cast<Berserk>(other);
	if (downcasted_other == nullptr) {
		return false;
	}

	return abilityChance == downcasted_other->abilityChance;
}
//-------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------

CharacterList::CharacterList(const CharacterList& other)
{
	const auto n = other.size();
	_characters.reserve(n);
	for (int i = 0; i < n; ++i) {
		_characters.push_back(other[i]->clone());
	}
}

int CharacterList:: size() const
{
	return static_cast<int>(_characters.size());
}
CharacterList& CharacterList:: operator=(const CharacterList& rhs) 
{
	CharacterList copy(rhs);
	copy.swap(*this);
	return *this;
}
CharacterPtr CharacterList::operator[](const int index) const 
{
	if (index >= this->size() || index < 0) 
	{
		throw runtime_error("CharacterList::operator[]  invalid index");
	}
	return _characters[index];
}
void CharacterList::swap(CharacterList& other)
{
	std::swap(this->_characters, other._characters);
}
void CharacterList::insert(CharacterPtr ch)
{	
	_characters.push_back(ch);
}
void CharacterList::insert(CharacterPtr ch,int index)
{
	CharacterList _characters2 = CharacterList(*this);
	CharacterList ch3;
	cout << max(this->size() + 1, index + 1)<<endl;
	ch3._characters.reserve(max(this->size()+1, index+1));

	for (int i = 0; i < max(this->size()+1,index); ++i) 
	{

		if (i < index)
		{
			ch3._characters.push_back(_characters2[i]);
			
		}
		else if (i == index)
		{
			ch3._characters.push_back(ch);

		}
		else
		{
			ch3._characters.push_back( _characters2[i-1]);
		}
		cout << ch3[i]->get_name()<<endl;
		_characters = ch3._characters;
	}
}

void CharacterList::remove(int index) 
{
	auto iter = _characters.cbegin(); // указатель на первый элемент
	_characters.erase(iter + index); 
}

//-------------------------------------------------------------------------------------------

int character :: index_of_strongest_hero(const CharacterList& characters)
{
	float max_damage = 0.f;
	int index = 0;
	for (int i = 0; i < characters.size(); ++i)
	{
		int value = characters[i]->get_damage();
		if (value > max_damage)
		{
			max_damage = value;
			index = i;
		}
	}
	return index;
}





