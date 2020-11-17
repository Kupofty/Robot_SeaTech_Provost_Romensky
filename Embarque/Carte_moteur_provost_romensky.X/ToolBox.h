/* 
 * File:   ToolBox.h
 * Author: TABLE 6
 *
 * Created on 29 septembre 2020, 12:22
 */

#ifndef TOOLBOX_H
#define	TOOLBOX_H

#define PI 3.141592653589793
float Abs(float value);
float Max(float value, float value2);
float Min(float value, float value2);
float LimitToInterval(float value, float lowLimit, float highLimit);
float RadianToDegree(float value);
float DegreeToRadian(float value);

#endif	/* TOOLBOX_H */

