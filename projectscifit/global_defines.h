/* 
 * File: global_defines.h  
 * Author: Anil Celik Maral  
 * Email: anilcelikmaral@gmail.com  
 * Brief: Defines for daily nutritional values and system wide defines
 * Created on August 27, 2017  
 */

#ifndef GLOBAL_DEFINES_H
#define GLOBAL_DEFINES_H

/* System wide defines */

/* NIL is used instead of NULL just in case the system doesn't define
   NULL. */
# ifndef NIL
# define NIL (void *) 0
# endif

/* Daily Nutritional Values */

/* The daily values are taken from FDA based on a person who takes
 2000 calories.
 https://www.fda.gov/Food/GuidanceRegulation/
 GuidanceDocumentsRegulatoryInformation/LabelingNutrition/ucm064928.htm
 */  

/* Main Nutriens */  

# ifndef DAILY_TOTAL_FAT   // In grams(g).  
# define DAILY_TOTAL_FAT 65u
# endif

# ifndef DAILY_SATURATED_FAT   // In grams(g).  
# define DAILY_SATURATED_FAT 20u
# endif

# ifndef DAILY_TOTAL_CARBOHYDRATE   // In grams(g).  
# define DAILY_TOTAL_CARBOHYDRATE 300u
# endif

# ifndef DAILY_PROTEIN   // In grams(g).  
# define DAILY_PROTEIN 50u
# endif

/* Vitamins */  

# ifndef DAILY_VITAMIN_A   // In international units(IU).  
# define DAILY_VITAMIN_A 5000u
# endif

# ifndef DAILY_VITAMIN_C   // In milligrams(mg).  
# define DAILY_VITAMIN_C 60u
# endif

# ifndef DAILY_VITAMIN_D   // In international units(IU).  
# define DAILY_VITAMIN_D 400u
# endif

# ifndef DAILY_VITAMIN_E   // In international units(IU).  
# define DAILY_VITAMIN_E 30u
# endif

# ifndef DAILY_VITAMIN_K   // In micrograms(ug).  
# define DAILY_VITAMIN_K 80u
# endif

# ifndef DAILY_NIACIN   // In milligrams(mg).  
# define DAILY_NIACIN 20u
# endif

# ifndef DAILY_THIAMIN   // In milligrams(mg).  
# define DAILY_THIAMIN 1.5u
# endif

# ifndef DAILY_BIOTIN   // In micrograms(ug).  
# define DAILY_BIOTIN 300u
# endif

# ifndef DAILY_RIBOFLAVIN   // In milligrams(mg).  
# define DAILY_RIBOFLAVIN 1.7u
# endif

# ifndef DAILY_PANTOTHENIC_ACID   // In milligrams(mg).  
# define DAILY_PANTOTHENIC_ACID 10u
# endif

# ifndef DAILY_VITAMIN_B6   // In milligrams(mg).  
# define DAILY_VITAMIN_B6 2u
# endif

# ifndef DAILY_VITAMIN_B12   // In micrograms(ug).  
# define DAILY_VITAMIN_B12 6u
# endif

/* Minerals */

# ifndef DAILY_SODIUM   // In milligrams(mg).  
# define DAILY_SODIUM 2400u
# endif

# ifndef DAILY_POTASSIUM   // In milligrams(mg).  
# define DAILY_POTASSIUM 3500u
# endif

# ifndef DAILY_IRON   // In milligrams(mg).  
# define DAILY_IRON 18u
# endif

# ifndef DAILY_CALCIUM   // In milligrams(mg).  
# define DAILY_CALCIUM 1000u
# endif

# ifndef DAILY_MAGNESIUM   // In milligrams(mg).  
# define DAILY_MAGNESIUM 1000u
# endif

# ifndef DAILY_PHOSPORUS   // In milligrams(mg).  
# define DAILY_PHOSPORUS 1000u
# endif

# ifndef DAILY_IODINE   // In micrograms(ug).  
# define DAILY_IODINE 150u
# endif

# ifndef DAILY_ZINC   // In milligrams(mg).  
# define DAILY_ZINC 15u
# endif

# ifndef DAILY_COPPER   // In milligrams(mg).  
# define DAILY_COPPER 2u
# endif

# ifndef DAILY_MANGANESE   // In milligrams(mg).  
# define DAILY_MANGANESE 2u
# endif

# ifndef DAILY_SELENIUM   // In micrograms(ug).  
# define DAILY_SELENIUM 70u
# endif

# ifndef DAILY_CHROMIUM   // In micrograms(ug).  
# define DAILY_CHROMIUM 120u
# endif

# ifndef DAILY_CHLORIDE   // In milligrams(mg).  
# define DAILY_CHLORIDE 3400u
# endif

# ifndef DAILY_MOLYBDENUM   // In micrograms(ug).  
# define DAILY_MOLYBDENUM  75u
# endif

/* Others */

# ifndef DAILY_DIETARY_FIBER   // In grams(g).  
# define DAILY_DIETARY_FIBER 25u
# endif

# ifndef DAILY_CHOLESTEROL   // In milligrams(mg).  
# define DAILY_CHOLESTEROL 300u
# endif

#endif /* GLOBAL_DEFINES_H */