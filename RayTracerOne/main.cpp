#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <cmath>
#include <random>
#include <thread>

#include "vec3.h"
#include "ray.h"
#include "defocus_camera.h"
#include "hittable.h"
#include "hittable_list.h"
#include "sphear.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"

using namespace cv;
using namespace std;

const int pieces = 3;
const int viewport_width = 960;
const int viewport_height = 480;
const int antialiasing = 100;

vec3 color(const ray &r, const hittable &world, int depth) {
	if (depth == 0) return vec3(0.5f, 0.5f, 0.5f);
	hit_result hitres;
	
	if (world.hits(r, 0.001f, numeric_limits<float>::max(), hitres)) {
		vec3 attenuation;
		ray reflection;
		if(hitres.mat_ptr->scatter(r, hitres, attenuation, reflection))
			return attenuation * color(reflection, world, depth - 1);
		else return vec3(0.0f, 0.0f, 0.0f);
	}
	vec3 ud = unit_vector(r.direction());
	float t = 0.5f * (ud.y() + 1.0f);
	return t * vec3(0.5f, 0.7f, 1.0f) +(1.0f - t) * vec3(1.0f, 1.0f, 1.0f);
}

hittable_list world;

void build_image(Mat *output, camera *cam, int bg, int en) {
	uchar* line;
	for (int i = 0; i < viewport_height; ++i) {
		line = output->ptr<uchar>(i);
		for (int j = bg; j < en; ++j) {
			vec3 col(0.0f, 0.0f, 0.0f);
			for (int k = 0; k < antialiasing; ++k) {
				float u = float(viewport_height - i - 1 + frand()) / viewport_height;
				float v = float(j + frand()) / viewport_width;
				ray r = cam->get_ray(u, v);
				col += color(r, world, 50);
			}
			col /= (float)antialiasing;
			col = vec3(sqrtf(col.r()), sqrtf(col.g()), sqrtf(col.b()));
			line[3 * j + 0] = uchar(255.9f * col.b());
			line[3 * j + 1] = uchar(255.9f * col.g());
			line[3 * j + 2] = uchar(255.9f * col.r());
		}
	}
}

int main(int argc, char** argv)
{
	hittable *some[200];
	some[0] = new sphere(vec3(0.0f, 0.0f, -1.0f), 0.5f, new lambertian{vec3( 0.8f, 0.3f, 0.3f )});
	some[1] = new sphere(vec3(-1.0f, 0.0f, -1.0f), 0.5f, new dielectric(1.5f));
	some[2] = new sphere(vec3(-1.0f, 0.0f, -1.0f), -0.45f, new dielectric(1.5f));
	some[3] = new sphere(vec3(1.0f, 0.0f, -1.0f), 0.5f, new metal(vec3(0.5f, 0.5f, 0.5f), 0.05f));
	some[4] = new sphere(vec3(0.0f, -50.5f, -1.0f), 50.0f, new lambertian{vec3( 0.8f, 0.8f, 0.3f )});
	int items = 5; int metals = 0, lamberts = 0, spheres = 0, balls = 0;
	for (int a = -5; a < 3; ++a) {
		for (int b = -5; b < 3; ++b) {
			vec3 center{ float(a) + frand() * 0.6f, -0.2f - frand() / 4.0f, float(b) + frand() * 0.6f };
			bool notClose = true;
			for (int k = 0; k < 4; ++k) {
				if ((center - static_cast<sphere*>(some[k])->C).length() < 1.1f) {
					notClose = false;
					break;
				}
			}
			if (!notClose) continue;
			int type = std::rand() % 3;
			if (type == 0) {
				++lamberts;
				some[items++] = new sphere(
					center,
					0.2f, new lambertian{ vec3(frand(), frand(), frand()) }
				);
			}
			else if (type == 1) {
				dielectric *material = new dielectric{ frand() + 1.1f };
				some[items++] = new sphere(center, 0.2f, material);
				if (std::rand() % 2 == 0) {
					some[items++] = new sphere(center, -0.19f, material);
					++spheres;
				}
				else ++balls;
			}
			else if (type == 2) {
				++metals;
				some[items++] = new sphere(
					center,
					0.2f, new metal{ vec3(frand(), frand(), frand()), frand() / 2.0f }
				);
			}
		}
	}
	std::cout << "World: "
		<< lamberts << " lamberts "
		<< metals << " metals "
		<< spheres << " spheres "
		<< balls << " balls, total = " << items << std::endl;
	world.list = some;
	world.size = items;
	char *filename = (char*)(malloc(25));
	for (int i = -360; i < 360; ++i) {
		Mat image{ viewport_height, viewport_width, CV_8UC3, Scalar{ 0,0,0 } };

		vec3 lookfrom(sinf(float(i) * float(CV_PI) / 720.0f) * 4.0f, 0.5f, cosf(float(i) * float(CV_PI) / 720.0f) * 4.0f),
			lookat(0.0f, 0.0f, -0.5f);
		defocus_camera cam(
			//vec3(-2.0f, 2.0f, 1.0f),
			lookfrom,
			lookat,
			vec3(0.0f, 1.0f, 0.0f),
			60.0f, float(viewport_width) / float(viewport_height),
			0.2f, (lookfrom - lookat).length()
		);

		int m = viewport_width / 3;
    // build_image(image, cam, 0, viewport_width);
		thread t1{ build_image, &image, &cam, 0, m};
		thread t2{ build_image, &image, &cam, m, 2 * m };
		thread t3{ build_image, &image, &cam, 2 * m, viewport_width };
		t1.join();
		t2.join();
		t3.join();

		sprintf(filename, "./film/image-%.3d.jpeg", i + 361);

		imwrite(filename, image);

		std::cout << "image " << i << " finished." << std::endl;
	}
	/*int median = 0;
	thread* workers[pieces];
	for (int i = 1; i <= pieces; ++i) {
		int next_median = viewport_width * i / pieces;
		std::cout << "Piece " << i << " " << median << " -> " << next_median << std::endl;
		workers[i - 1] = new thread{ build_image, median, next_median };
		median = next_median;
	}
	for (int i = 0; i < pieces; i++)
		workers[i]->join();*/

	//int report_count = viewport_height / 10, reported_count = 0;
	//if (i / report_count > reported_count) {
	//	std::cout << "Covered " << (i * 100 / viewport_height) << "%" << std::endl;
	//	reported_count = i / report_count;
	//}

	//namedWindow("Display window", WINDOW_AUTOSIZE); // Create a window for display.
	//imshow("Display window", image); // Show our image inside it.

	//waitKey(0); // Wait for a keystroke in the window
	return 0;
}
