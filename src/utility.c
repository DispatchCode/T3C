/* #########################################################
 * Description: Just some utility functions used for index
 *            : calculation or the the min/max of two numbers
 * #########################################################
 */

#include "../include/utils.h"


inline int spatial_coords_2_index(spatial_coords coords)
{
	return coords.x * 3 + coords.y;
}

inline spatial_coords index_to_xy(int index)
{
	spatial_coords coords;
	coords.x = index / 3;
	coords.y = index % 3;

	return coords;
}

inline double min_value(double n1, double n2)
{
	return (n1 <= n2) ? n1 : n2;
}

inline double max_value(double n1, double n2)
{
	return (n1 >= n2) ? n1 : n2;
}
