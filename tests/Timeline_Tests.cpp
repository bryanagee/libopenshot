/**
 * @file
 * @brief Unit tests for openshot::Timeline
 * @author Jonathan Thomas <jonathan@openshot.org>
 *
 * @section LICENSE
 *
 * Copyright (c) 2008-2014 OpenShot Studios, LLC
 * <http://www.openshotstudios.com/>. This file is part of
 * OpenShot Library (libopenshot), an open-source project dedicated to
 * delivering high quality video editing and animation solutions to the
 * world. For more information visit <http://www.openshot.org/>.
 *
 * OpenShot Library (libopenshot) is free software: you can redistribute it
 * and/or modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * OpenShot Library (libopenshot) is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with OpenShot Library. If not, see <http://www.gnu.org/licenses/>.
 */

#include "UnitTest++.h"
#include "../include/OpenShot.h"

using namespace std;
using namespace openshot;

TEST(Timeline_Constructor)
{
	// Create a default fraction (should be 1/1)
	Fraction fps(30000,1000);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK_EQUAL(640, t1.info.width);
	CHECK_EQUAL(480, t1.info.height);

	// Create a default fraction (should be 1/1)
	Timeline t2(300, 240, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK_EQUAL(300, t2.info.width);
	CHECK_EQUAL(240, t2.info.height);
}

TEST(Timeline_Width_and_Height_Functions)
{
	// Create a default fraction (should be 1/1)
	Fraction fps(30000,1000);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK_EQUAL(640, t1.info.width);
	CHECK_EQUAL(480, t1.info.height);

	// Set width
	t1.info.width = 600;

	// Check values
	CHECK_EQUAL(600, t1.info.width);
	CHECK_EQUAL(480, t1.info.height);

	// Set height
	t1.info.height = 400;

	// Check values
	CHECK_EQUAL(600, t1.info.width);
	CHECK_EQUAL(400, t1.info.height);
}

TEST(Timeline_Framerate)
{
	// Create a default fraction (should be 1/1)
	Fraction fps(24,1);
	Timeline t1(640, 480, fps, 44100, 2, LAYOUT_STEREO);

	// Check values
	CHECK_CLOSE(24.0f, t1.info.fps.ToFloat(), 0.00001);
}

TEST(Timeline_Check_Two_Track_Video)
{
	// Create a reader
	Clip clip_video("../../src/examples/test.mp4");
	clip_video.Layer(0);
	clip_video.Position(0.0);

	Clip clip_overlay("../../src/examples/front3.png");
	clip_overlay.Layer(1);
	clip_overlay.Position(0.05); // Delay the overlay by 0.05 seconds
	clip_overlay.End(0.5);	// Make the duration of the overlay 1/2 second

	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add clips
	t.AddClip(&clip_video);
	t.AddClip(&clip_overlay);

	// Open Timeline
	t.Open();

	// Get frame
	tr1::shared_ptr<Frame> f = t.GetFrame(1);

	// Get the image data
	const unsigned char* pixels = f->GetPixels(200);
	int pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(21, (int)pixels[pixel_index]);
	CHECK_EQUAL(191, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(0, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Get frame
	f = t.GetFrame(2);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(252, (int)pixels[pixel_index]);
	CHECK_EQUAL(252, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(249, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Get frame
	f = t.GetFrame(3);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(25, (int)pixels[pixel_index]);
	CHECK_EQUAL(189, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(0, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);


	// Get frame
	f = t.GetFrame(24);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(251, (int)pixels[pixel_index]);
	CHECK_EQUAL(251, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(248, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Get frame
	f = t.GetFrame(5);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(25, (int)pixels[pixel_index]);
	CHECK_EQUAL(189, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(0, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Get frame
	f = t.GetFrame(25);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(251, (int)pixels[pixel_index]);
	CHECK_EQUAL(251, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(248, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Get frame
	f = t.GetFrame(4);

	// Get scanline 190 of pixels
	pixels = f->GetPixels(190);
	pixel_index = 230 * 4; // pixel 230 (4 bytes per pixel)

	// Check image properties
	CHECK_EQUAL(252, (int)pixels[pixel_index]);
	CHECK_EQUAL(250, (int)pixels[pixel_index + 1]);
	CHECK_EQUAL(247, (int)pixels[pixel_index + 2]);
	CHECK_EQUAL(255, (int)pixels[pixel_index + 3]);

	// Close reader
	t.Close();
}

TEST(Timeline_Clip_Order)
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add some clips out of order
	Clip clip_top("../../src/examples/front3.png");
	clip_top.Layer(2);
	t.AddClip(&clip_top);

	Clip clip_middle("../../src/examples/front.png");
	clip_middle.Layer(0);
	t.AddClip(&clip_middle);

	Clip clip_bottom("../../src/examples/back.png");
	clip_bottom.Layer(1);
	t.AddClip(&clip_bottom);

	// Open Timeline
	t.Open();

	// Loop through Clips and check order (they should have been sorted into the correct order)
	// Bottom layer to top layer, then by position.
	list<Clip*>::iterator clip_itr;
	list<Clip*> clips = t.Clips();
	int counter = 0;
	for (clip_itr=clips.begin(); clip_itr != clips.end(); ++clip_itr)
	{
		// Get clip object from the iterator
		Clip *clip = (*clip_itr);

		switch (counter) {
		case 0:
			CHECK_EQUAL(0, clip->Layer());
			break;
		case 1:
			CHECK_EQUAL(1, clip->Layer());
			break;
		case 2:
			CHECK_EQUAL(2, clip->Layer());
			break;
		}

		// increment counter
		counter++;
	}

	// Add another clip
	Clip clip_middle1("../../src/examples/interlaced.png");
	clip_middle1.Layer(1);
	clip_middle1.Position(0.5);
	t.AddClip(&clip_middle1);


	// Loop through clips again, and re-check order
	counter = 0;
	clips = t.Clips();
	for (clip_itr=clips.begin(); clip_itr != clips.end(); ++clip_itr)
	{
		// Get clip object from the iterator
		Clip *clip = (*clip_itr);

		switch (counter) {
		case 0:
			CHECK_EQUAL(0, clip->Layer());
			break;
		case 1:
			CHECK_EQUAL(1, clip->Layer());
			CHECK_CLOSE(0.0, clip->Position(), 0.0001);
			break;
		case 2:
			CHECK_EQUAL(1, clip->Layer());
			CHECK_CLOSE(0.5, clip->Position(), 0.0001);
			break;
		case 3:
			CHECK_EQUAL(2, clip->Layer());
			break;
		}

		// increment counter
		counter++;
	}

	// Close reader
	t.Close();
}


TEST(Timeline_Effect_Order)
{
	// Create a timeline
	Timeline t(640, 480, Fraction(30, 1), 44100, 2, LAYOUT_STEREO);

	// Add some effects out of order
	Negate effect_top;
	effect_top.Id("C");
	effect_top.Layer(2);
	t.AddEffect(&effect_top);

	Negate effect_middle;
	effect_middle.Id("A");
	effect_middle.Layer(0);
	t.AddEffect(&effect_middle);

	Negate effect_bottom;
	effect_bottom.Id("B");
	effect_bottom.Layer(1);
	t.AddEffect(&effect_bottom);

	// Open Timeline
	t.Open();

	// Loop through effects and check order (they should have been sorted into the correct order)
	// Bottom layer to top layer, then by position, and then by order.
	list<EffectBase*>::iterator effect_itr;
	list<EffectBase*> effects = t.Effects();
	int counter = 0;
	for (effect_itr=effects.begin(); effect_itr != effects.end(); ++effect_itr)
	{
		// Get clip object from the iterator
		EffectBase *effect = (*effect_itr);

		switch (counter) {
		case 0:
			CHECK_EQUAL(0, effect->Layer());
			CHECK_EQUAL("A", effect->Id());
			CHECK_EQUAL(0, effect->Order());
			break;
		case 1:
			CHECK_EQUAL(1, effect->Layer());
			CHECK_EQUAL("B", effect->Id());
			CHECK_EQUAL(0, effect->Order());
			break;
		case 2:
			CHECK_EQUAL(2, effect->Layer());
			CHECK_EQUAL("C", effect->Id());
			CHECK_EQUAL(0, effect->Order());
			break;
		}

		// increment counter
		counter++;
	}

	// Add some more effects out of order
	Negate effect_top1;
	effect_top1.Id("B-2");
	effect_top1.Layer(1);
	effect_top1.Position(0.5);
	effect_top1.Order(2);
	t.AddEffect(&effect_top1);

	Negate effect_middle1;
	effect_middle1.Id("B-3");
	effect_middle1.Layer(1);
	effect_middle1.Position(0.5);
	effect_middle1.Order(1);
	t.AddEffect(&effect_middle1);

	Negate effect_bottom1;
	effect_bottom1.Id("B-1");
	effect_bottom1.Layer(1);
	effect_bottom1.Position(0);
	effect_bottom1.Order(3);
	t.AddEffect(&effect_bottom1);


	// Loop through effects again, and re-check order
	effects = t.Effects();
	counter = 0;
	for (effect_itr=effects.begin(); effect_itr != effects.end(); ++effect_itr)
	{
		// Get clip object from the iterator
		EffectBase *effect = (*effect_itr);

		switch (counter) {
		case 0:
			CHECK_EQUAL(0, effect->Layer());
			CHECK_EQUAL("A", effect->Id());
			CHECK_EQUAL(0, effect->Order());
			break;
		case 1:
			CHECK_EQUAL(1, effect->Layer());
			CHECK_EQUAL("B-1", effect->Id());
			CHECK_CLOSE(0.0, effect->Position(), 0.0001);
			CHECK_EQUAL(3, effect->Order());
			break;
		case 2:
			CHECK_EQUAL(1, effect->Layer());
			CHECK_EQUAL("B", effect->Id());
			CHECK_CLOSE(0.0, effect->Position(), 0.0001);
			CHECK_EQUAL(0, effect->Order());
			break;
		case 3:
			CHECK_EQUAL(1, effect->Layer());
			CHECK_EQUAL("B-2", effect->Id());
			CHECK_CLOSE(0.5, effect->Position(), 0.0001);
			CHECK_EQUAL(2, effect->Order());
			break;
		case 4:
			CHECK_EQUAL(1, effect->Layer());
			CHECK_EQUAL("B-3", effect->Id());
			CHECK_CLOSE(0.5, effect->Position(), 0.0001);
			CHECK_EQUAL(1, effect->Order());
			break;
		case 5:
			CHECK_EQUAL(2, effect->Layer());
			CHECK_EQUAL("C", effect->Id());
			CHECK_EQUAL(0, effect->Order());
			break;
		}

		// increment counter
		counter++;
	}

	// Close reader
	t.Close();
}
