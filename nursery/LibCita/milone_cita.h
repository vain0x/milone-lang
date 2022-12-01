#include <milone.h>
#include <stdio.h>
#include <stdlib.h>

// the code is edited based on generated output

struct CiData;
struct CiEntry;

struct CiArray {
    struct CiData const *ptr;
    int32_t len;
};
struct CiMap {
    struct CiEntry const *ptr;
    int32_t len;
};

enum CiType {
    CiType_Null,
    CiType_Bool,
    CiType_Int,
    CiType_Int64,
    CiType_UInt64,
    CiType_F64,
    CiType_String,
    CiType_Array,
    CiType_Map,
    CiType_Foreign
};

struct CiData {
    enum CiType discriminant;
    union {
        bool bool_value;
        int32_t int_value;
        int64_t int64;
        uint64_t uInt64;
        double f64;
        struct String string;
        struct CiArray const *array;
        struct CiMap const *map;
        void *foreign;
    };
};

typedef enum CiType CiType;
typedef struct CiArray CiArray;
typedef struct CiMap CiMap;
typedef struct CiData CiData;
typedef struct CiEntry CiEntry;

struct CiData CiData_null(void);

struct CiData CiData_ofBool(bool value_1);

struct CiData CiData_ofInt(int32_t value_2);

struct CiData CiData_ofInt64(int64_t value_3);

struct CiData CiData_ofUInt64(uint64_t value_4);

struct CiData CiData_ofF64(double value_5);

struct CiData CiData_ofString(struct String value_6);

struct CiData CiData_unsafeOfCString(char const *value_7);

struct CiData CiData_emptyArray(void);

struct CiData CiData_unsafeWrapArray(struct CiArray array_);

struct CiData CiData_emptyMap(void);

struct CiData CiData_unsafeWrapMap(struct CiMap map_);

struct CiData CiData_createForeign(void *ptr_);

struct CiEntry CiEntry_create(struct String key_, struct CiData value_8);

struct String CiEntry_key(struct CiEntry e_);

struct CiData CiEntry_value(struct CiEntry e_1);

bool CiData_isNull(struct CiData value_10);

bool CiData_asBool(struct CiData value_11, bool *writtenTo_);

bool CiData_asInt(struct CiData value_13, int32_t *writtenTo_1);

bool CiData_asInt64(struct CiData value_15, int64_t *writtenTo_2);

bool CiData_asUInt64(struct CiData value_17, uint64_t *writtenTo_3);

bool CiData_asF64(struct CiData value_19, double *writtenTo_4);

bool CiData_asArray(struct CiData value_21, struct CiArray *writtenTo_5);

bool CiData_asMap(struct CiData value_23, struct CiMap *writtenTo_6);

bool CiData_asForeign(struct CiData value_25, void **writtenTo_7);
