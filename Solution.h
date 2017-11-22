#pragma once
#include "Common.h"
#include <cliext/utility>

ref struct Skill;
ref struct Ability;
ref struct Armor;
ref struct Charm;
ref struct ArmorEquivalence;
ref struct Decoration;
ref struct AbilityPair;
ref struct Weapon;

typedef System::Collections::Generic::Dictionary< Ability^, int > AbilityMap;

ref struct Query : public System::Object
{
	List_t< Skill^ > skills;
	HunterType hunter_type;
	Gender gender;
	unsigned hr, elder_star, weapon_slots_allowed;
	bool include_arena, allow_bad, allow_event, allow_lower_tier, allow_japs, allow_excavated, add_extra;

	List_t< List_t< Armor^ >^ > rel_armor, inf_armor;
	List_t< Weapon^ > rel_weapons;
	List_t< Ability^ > rel_abilities;
	List_t< Decoration^ > rel_decorations, inf_decorations;
};


ref struct ThreadSearchData
{
	Query^ query;
	Charm^ charm_template;
	Armor^ helm;
};

ref struct CalculationData;

ref struct Solution
{
	List_t< Armor^ > armors;
	List_t< Decoration^ > decorations, body_decorations, non_body_decorations;
	List_t< Skill^ > extra_skills, bad_skills, potential_extra_skills;
	AbilityMap abilities;
	Charm^ charm;
	Weapon^ weapon;

	unsigned torso_slots_spare, total_slots_spare;
	int fire_res, ice_res, water_res, thunder_res, dragon_res, extra_skill_score, torso_multiplier;
	unsigned defence, max_defence, rarity, difficulty;
	array< unsigned >^ slots_spare, ^family_score;
	bool doubled, reordered_to_fix;

	bool MatchesQuery( Query^ query );
	void CalculateData( const unsigned hr, const unsigned elder_star );
	void CalculateFamilyScore();
	void CalculateExtraSkillScore( const unsigned hr, const unsigned elder_star );

private:
	CalculationData^ data;

	bool FixBadSkill( Skill^ skill );
	bool FixBadSkills();
	bool CheckBadSkills();
	Decoration^ Count1SocketGems( Ability^ ability, int& num );
	int GetReplacable( Ability^ ability, unsigned slots );
	bool ReorderGems();
	void Replace( const unsigned index, Decoration^ decoration );
	void CalculateExtraSkills();
	void ReduceSlots();
	void ReduceSkills();
	void ReduceCharm();
	void RearrangeDecorations();
	void AddExtraSkills();
};
