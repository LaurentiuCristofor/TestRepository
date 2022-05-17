#ifndef MONSTER_READER_H
#define MONSTER_READER_H

/* Generated by flatcc 0.6.1-dev FlatBuffers schema compiler for C by dvide.com */

#ifndef FLATBUFFERS_COMMON_READER_H
#include "flatbuffers_common_reader.h"
#endif
#include "flatcc/flatcc_flatbuffers.h"
#ifndef __alignas_is_defined
#include <stdalign.h>
#endif
#include "flatcc/flatcc_prologue.h"
#ifndef flatbuffers_identifier
#define flatbuffers_identifier 0
#endif
#ifndef flatbuffers_extension
#define flatbuffers_extension ".bin"
#endif

typedef struct Flatbuffers_Monster_Vec3 Flatbuffers_Monster_Vec3_t;
typedef const Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3_struct_t;
typedef Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3_mutable_struct_t;
typedef const Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3_vec_t;
typedef Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3_mutable_vec_t;

typedef const struct Flatbuffers_Monster_Monster_table *Flatbuffers_Monster_Monster_table_t;
typedef struct Flatbuffers_Monster_Monster_table *Flatbuffers_Monster_Monster_mutable_table_t;
typedef const flatbuffers_uoffset_t *Flatbuffers_Monster_Monster_vec_t;
typedef flatbuffers_uoffset_t *Flatbuffers_Monster_Monster_mutable_vec_t;
typedef const struct Flatbuffers_Monster_Weapon_table *Flatbuffers_Monster_Weapon_table_t;
typedef struct Flatbuffers_Monster_Weapon_table *Flatbuffers_Monster_Weapon_mutable_table_t;
typedef const flatbuffers_uoffset_t *Flatbuffers_Monster_Weapon_vec_t;
typedef flatbuffers_uoffset_t *Flatbuffers_Monster_Weapon_mutable_vec_t;
#ifndef Flatbuffers_Monster_Vec3_file_identifier
#define Flatbuffers_Monster_Vec3_file_identifier flatbuffers_identifier
#endif
/* deprecated, use Flatbuffers_Monster_Vec3_file_identifier */
#ifndef Flatbuffers_Monster_Vec3_identifier
#define Flatbuffers_Monster_Vec3_identifier flatbuffers_identifier
#endif
#define Flatbuffers_Monster_Vec3_type_hash ((flatbuffers_thash_t)0x46228d96)
#define Flatbuffers_Monster_Vec3_type_identifier "\x96\x8d\x22\x46"
#ifndef Flatbuffers_Monster_Monster_file_identifier
#define Flatbuffers_Monster_Monster_file_identifier flatbuffers_identifier
#endif
/* deprecated, use Flatbuffers_Monster_Monster_file_identifier */
#ifndef Flatbuffers_Monster_Monster_identifier
#define Flatbuffers_Monster_Monster_identifier flatbuffers_identifier
#endif
#define Flatbuffers_Monster_Monster_type_hash ((flatbuffers_thash_t)0xbc5d3f05)
#define Flatbuffers_Monster_Monster_type_identifier "\x05\x3f\x5d\xbc"
#ifndef Flatbuffers_Monster_Weapon_file_identifier
#define Flatbuffers_Monster_Weapon_file_identifier flatbuffers_identifier
#endif
/* deprecated, use Flatbuffers_Monster_Weapon_file_identifier */
#ifndef Flatbuffers_Monster_Weapon_identifier
#define Flatbuffers_Monster_Weapon_identifier flatbuffers_identifier
#endif
#define Flatbuffers_Monster_Weapon_type_hash ((flatbuffers_thash_t)0xcd7d3f05)
#define Flatbuffers_Monster_Weapon_type_identifier "\x05\x3f\x7d\xcd"

typedef int8_t Flatbuffers_Monster_Color_enum_t;
__flatbuffers_define_integer_type(Flatbuffers_Monster_Color, Flatbuffers_Monster_Color_enum_t, 8)
#define Flatbuffers_Monster_Color_Red ((Flatbuffers_Monster_Color_enum_t)INT8_C(0))
#define Flatbuffers_Monster_Color_Green ((Flatbuffers_Monster_Color_enum_t)INT8_C(1))
#define Flatbuffers_Monster_Color_Blue ((Flatbuffers_Monster_Color_enum_t)INT8_C(2))

static inline const char *Flatbuffers_Monster_Color_name(Flatbuffers_Monster_Color_enum_t value)
{
    switch (value) {
    case Flatbuffers_Monster_Color_Red: return "Red";
    case Flatbuffers_Monster_Color_Green: return "Green";
    case Flatbuffers_Monster_Color_Blue: return "Blue";
    default: return "";
    }
}

static inline int Flatbuffers_Monster_Color_is_known_value(Flatbuffers_Monster_Color_enum_t value)
{
    switch (value) {
    case Flatbuffers_Monster_Color_Red: return 1;
    case Flatbuffers_Monster_Color_Green: return 1;
    case Flatbuffers_Monster_Color_Blue: return 1;
    default: return 0;
    }
}


struct Flatbuffers_Monster_Vec3 {
    alignas(4) float x;
    alignas(4) float y;
    alignas(4) float z;
};
static_assert(sizeof(Flatbuffers_Monster_Vec3_t) == 12, "struct size mismatch");

static inline const Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3__const_ptr_add(const Flatbuffers_Monster_Vec3_t *p, size_t i) { return p + i; }
static inline Flatbuffers_Monster_Vec3_t *Flatbuffers_Monster_Vec3__ptr_add(Flatbuffers_Monster_Vec3_t *p, size_t i) { return p + i; }
static inline Flatbuffers_Monster_Vec3_struct_t Flatbuffers_Monster_Vec3_vec_at(Flatbuffers_Monster_Vec3_vec_t vec, size_t i)
__flatbuffers_struct_vec_at(vec, i)
static inline size_t Flatbuffers_Monster_Vec3__size(void) { return 12; }
static inline size_t Flatbuffers_Monster_Vec3_vec_len(Flatbuffers_Monster_Vec3_vec_t vec)
__flatbuffers_vec_len(vec)
__flatbuffers_struct_as_root(Flatbuffers_Monster_Vec3)

__flatbuffers_define_struct_scalar_field(Flatbuffers_Monster_Vec3, x, flatbuffers_float, float)
__flatbuffers_define_struct_scalar_field(Flatbuffers_Monster_Vec3, y, flatbuffers_float, float)
__flatbuffers_define_struct_scalar_field(Flatbuffers_Monster_Vec3, z, flatbuffers_float, float)

typedef uint8_t Flatbuffers_Monster_Equipment_union_type_t;
__flatbuffers_define_integer_type(Flatbuffers_Monster_Equipment, Flatbuffers_Monster_Equipment_union_type_t, 8)
__flatbuffers_define_union(flatbuffers_, Flatbuffers_Monster_Equipment)
#define Flatbuffers_Monster_Equipment_NONE ((Flatbuffers_Monster_Equipment_union_type_t)UINT8_C(0))
#define Flatbuffers_Monster_Equipment_Weapon ((Flatbuffers_Monster_Equipment_union_type_t)UINT8_C(1))

static inline const char *Flatbuffers_Monster_Equipment_type_name(Flatbuffers_Monster_Equipment_union_type_t type)
{
    switch (type) {
    case Flatbuffers_Monster_Equipment_NONE: return "NONE";
    case Flatbuffers_Monster_Equipment_Weapon: return "Weapon";
    default: return "";
    }
}

static inline int Flatbuffers_Monster_Equipment_is_known_type(Flatbuffers_Monster_Equipment_union_type_t type)
{
    switch (type) {
    case Flatbuffers_Monster_Equipment_NONE: return 1;
    case Flatbuffers_Monster_Equipment_Weapon: return 1;
    default: return 0;
    }
}


struct Flatbuffers_Monster_Monster_table { uint8_t unused__; };

static inline size_t Flatbuffers_Monster_Monster_vec_len(Flatbuffers_Monster_Monster_vec_t vec)
__flatbuffers_vec_len(vec)
static inline Flatbuffers_Monster_Monster_table_t Flatbuffers_Monster_Monster_vec_at(Flatbuffers_Monster_Monster_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(Flatbuffers_Monster_Monster_table_t, vec, i, 0)
__flatbuffers_table_as_root(Flatbuffers_Monster_Monster)

__flatbuffers_define_struct_field(0, Flatbuffers_Monster_Monster, pos, Flatbuffers_Monster_Vec3_struct_t, 0)
__flatbuffers_define_scalar_field(1, Flatbuffers_Monster_Monster, mana, flatbuffers_int16, int16_t, INT16_C(150))
__flatbuffers_define_scalar_field(2, Flatbuffers_Monster_Monster, hp, flatbuffers_int16, int16_t, INT16_C(100))
__flatbuffers_define_string_field(3, Flatbuffers_Monster_Monster, name, 0)
/* Skipping deprecated field: 'Flatbuffers_Monster_Monster_friendly' */

__flatbuffers_define_vector_field(5, Flatbuffers_Monster_Monster, inventory, flatbuffers_uint8_vec_t, 0)
__flatbuffers_define_scalar_field(6, Flatbuffers_Monster_Monster, color, Flatbuffers_Monster_Color, Flatbuffers_Monster_Color_enum_t, INT8_C(2))
__flatbuffers_define_vector_field(7, Flatbuffers_Monster_Monster, weapons, Flatbuffers_Monster_Weapon_vec_t, 0)
__flatbuffers_define_union_field(flatbuffers_, 9, Flatbuffers_Monster_Monster, equipped, Flatbuffers_Monster_Equipment, 0)
__flatbuffers_define_vector_field(10, Flatbuffers_Monster_Monster, path, Flatbuffers_Monster_Vec3_vec_t, 0)

struct Flatbuffers_Monster_Weapon_table { uint8_t unused__; };

static inline size_t Flatbuffers_Monster_Weapon_vec_len(Flatbuffers_Monster_Weapon_vec_t vec)
__flatbuffers_vec_len(vec)
static inline Flatbuffers_Monster_Weapon_table_t Flatbuffers_Monster_Weapon_vec_at(Flatbuffers_Monster_Weapon_vec_t vec, size_t i)
__flatbuffers_offset_vec_at(Flatbuffers_Monster_Weapon_table_t, vec, i, 0)
__flatbuffers_table_as_root(Flatbuffers_Monster_Weapon)

__flatbuffers_define_string_field(0, Flatbuffers_Monster_Weapon, name, 0)
__flatbuffers_define_scalar_field(1, Flatbuffers_Monster_Weapon, damage, flatbuffers_int16, int16_t, INT16_C(0))


#include "flatcc/flatcc_epilogue.h"
#endif /* MONSTER_READER_H */