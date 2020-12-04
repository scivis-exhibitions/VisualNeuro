/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2020 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *********************************************************************************/

#pragma once

#include <modules/visualneuro/visualneuromoduledefine.h>
#include <inviwo/core/processors/poolprocessor.h>
#include <inviwo/core/properties/optionproperty.h>
#include <inviwo/core/properties/isotfproperty.h>
#include <inviwo/core/properties/raycastingproperty.h>
#include <inviwo/core/properties/simplelightingproperty.h>
#include <inviwo/core/properties/cameraproperty.h>
#include <inviwo/core/properties/compositeproperty.h>
#include <inviwo/core/properties/volumeindicatorproperty.h>
#include <inviwo/core/ports/imageport.h>
#include <inviwo/core/ports/volumeport.h>

#include <modules/opengl/shader/shader.h>

namespace inviwo {

/** \docpage{org.inviwo.BrainRayCaster, Brain Ray Caster}
* ![](org.inviwo.BrainRayCaster.png?classIdentifier=org.inviwo.BrainRayCaster)
* 
 * Processor for visualizing and fusing two sources of volumetric data by means of volume raycasting. 
 * Besides the volume data, entry and exit point locations of the bounding box are required. These
 * can be created with the EntryExitPoints processor. The camera properties between these
 * two processors need to be linked.
* 
* 
* ### Inports
*   * __volume__ Primary brain data (MRI scan)
*   * __activity__ Secondary brain data.
*   * __entry__ entry point locations of input volume (image generated by EntryExitPoints
 * processor)
*   * __exit__ exit point positions of input volume (image generated by EntryExitPoints
 * processor)
*   * __bg__ optional background image. The depth channel is used to terminated the raycasting.
*   * __atlas__ Brain region atlas.
*   * __atlasTransferFunction__ Brain region atlas color map.
* 
* ### Outports
*   * __outport__ output image containing volume rendering of the input
* 
* ### Properties (related to Brain Ray Caster)
*   * __Enable Atlas__ Show/hide brain atlas.
*   * __Activity transfer function__ Color map of secondary volume.
* 
*/

class IVW_MODULE_VISUALNEURO_API BrainRayCaster : public PoolProcessor {
public:
    BrainRayCaster();
    virtual ~BrainRayCaster() = default;

    virtual void initializeResources() override;

    virtual const ProcessorInfo getProcessorInfo() const override;
    static const ProcessorInfo processorInfo_;

protected:
    virtual void process() override;
    void raycast(const Volume& volume, const Volume& activity, const Volume& atlas);

    Shader shader_;
    VolumeInport volumePort_;
    VolumeInport activityPort_;
    ImageInport entryPort_;
    ImageInport exitPort_;
    VolumeInport atlasPort_;
    DataInport<TransferFunction> atlasTransferFunction_;
    ImageInport backgroundPort_;
    ImageOutport outport_;

    OptionPropertyInt channel_;
    RaycastingProperty raycasting_;
    BoolProperty enableAtlas_;
    IsoTFProperty isotfComposite_;
    TransferFunctionProperty activityTransferFunction_;

    CameraProperty camera_;
    SimpleLightingProperty lighting_;
    VolumeIndicatorProperty positionIndicator_;
};

}  // namespace inviwo