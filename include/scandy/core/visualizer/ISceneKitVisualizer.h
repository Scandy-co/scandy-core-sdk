/****************************************************************************\
 * Copyright (C) 2019 Scandy
 *
 * THIS CODE AND INFORMATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 \****************************************************************************/

// Do not distribute this file.

#ifndef Scandy_ISceneKitVisualizer_h
#define Scandy_ISceneKitVisualizer_h

#include <scandy/core/IScandyCoreConfiguration.h>

#if IOS
#import <SceneKit/SceneKit.h>
#import <AVFoundation/AVFoundation.h>
#else
namespace {
  class SCNMaterial{};
  class SCNNode{};
  class AVAudioPlayerNode{};
  class AVAudioMixerNode{};
}
#endif


namespace scandy { namespace core {
  class ISceneKitVisualizer
  {
  protected:
    SCNNode* m_render_delegate_node;
    SCNMaterial* m_material;
    int m_shader_idx;

    AVAudioPlayerNode* m_player_node;
    AVAudioMixerNode* m_mixer;
    float m_gain_level;

    bool m_loop_playback = true;
    bool m_paused = false;
    bool m_use_physics = false;

    uint8_t m_frame_skip = 0;
  public:
    ISceneKitVisualizer(
      void* _scene,
      std::shared_ptr<scandy::core::IScandyCoreConfiguration> sc_config
    ){}

    ~ISceneKitVisualizer(){}

    /**
     * Remove all the nodes connected to the ISceneKitVisualizer
     */
    virtual void clearNodes() {}

    /**
     * Detach this visualizer from the pipeline its connected to
     */
    virtual void detach() {}

    /**
     * Adjust the gain level on the audio playback
     * @param gain_level How high of a gain, 0.0 - 100.0
     */
    virtual void setGainLevel(float gain_level) {}

    /**
     * Sets the shader index to be used on the render node
     * @param shader_idx -1 disables, 0 -> shader count
     */
    virtual void setShaderIdx(float shader_idx) {}

    /**
     * Sets whether to loop over the source being played
     * NOTE: Not all ISceneKitVisualizer children use this prop.
     * @param loop True to loop, false to not loop
     */
    virtual void setLoops(bool loop) {}

    /**
     * Sets whether to pause the animation playback
     * @param paused True to pause, false to resume
     */
    virtual void setPaused(bool paused) {}

    /**
     * Sets whether or not the SCNNode's content should use a physics body
     * @param use_physics True to use physics, false no.
     */
    virtual void setUsePhysics(bool use_physics) {}

    /**
     * Adjust how many frames should be skipped when playing back from file
     * @param frame_skip The number of frames to skip after a frame is played. Defaults to 0, meaning every frame is played.
     */
    virtual void setFrameSkip(uint8_t frame_skip) {}

    /**
     * Sets the source directory to pull assets from.
     * NOTE: Not all ISceneKitVisualizer children use this prop.
     * @param source_directory Absolute path on local machine to directory
     */
    virtual void setSourceDirectory(std::string source_directory) {}

    /**
     * Get how many preprogrammed shaders there are to choose from
     * @return The number of available shaders
     */
    virtual int getNumberOfShaders(){ return 0;}

    /**
     * Get the SCNNode that is the parent for all the nodes being render
     * @return The SCNNode you asked for
     */
    virtual SCNNode* node() { return nullptr; }

    /**
     * Get the SCNMaterial that is being rendered through this Visualizer
     * @return The SCNMaterial you asked for
     */
    virtual SCNMaterial* material() { return nullptr; }
  };

}}

#endif // Scandy_ISceneKitVisualizer_h
