/*
 * TI Voxel Lib component.
 *
 * Copyright (c) 2014 Texas Instruments Inc.
 */

#ifndef VOXEL_CAMERASYSTEM_H
#define VOXEL_CAMERASYSTEM_H

#include <DepthCameraLibrary.h>
#include "DownloaderFactory.h"

namespace Voxel
{

/**
 * \defgroup CamSys Camera System Components
 * @{
 * \brief This group of classes provide the higher level API for cameras
 * @}
 */

/**
 * \ingroup CamSys
 * 
 * \brief This class provides ways to instantiate individual cameras and components like filters.
 */
class VOXEL_EXPORT CameraSystem
{
protected:
  tVector<DepthCameraLibraryPtr> _libraries;
  tMap<String, DepthCameraFactoryPtr> _factories; // Key = device ID as returned by Device::id()
  tMap<String, DepthCameraPtr> _depthCameras; // Key = device ID as returned by Device::id()
  
  tMap<String, FilterFactoryPtr> _filterFactories; // Key = filter name
  
  tMap<String, DownloaderFactoryPtr> _downloaderFactories;// Key = device ID as returned by Device::id()
  
  tMap<GeneratorIDType, DepthCameraFactoryPtr> _factoryForGeneratorID; // Key = frame generator ID
  
  void _init();
  
  void _loadLibraries(const tVector<String> &paths);
  
public:
  CameraSystem();
  
  bool addDepthCameraFactory(DepthCameraFactoryPtr factory);
  
  tVector<DevicePtr> scan();
  
  DepthCameraPtr connect(const DevicePtr &device);
  // Remove local reference. Outside calling function should remove reference to its DepthCamera as well
  bool disconnect(const DepthCameraPtr &depthCamera, bool reset = false);
  
  
  
  bool addFilterFactory(FilterFactoryPtr filterFactory);
  
  tVector<String> getSupportedFilters();
  bool getFilterDescription(const String &filterName, FilterDescription &description);
  FilterPtr createFilter(const String &name, DepthCamera::FrameType type);
  
  tVector<DevicePtr> getProgrammableDevices();
  bool addDownloaderFactory(DownloaderFactoryPtr downloaderFactory);
  DownloaderPtr getDownloader(const DevicePtr &device);
  
  bool getFrameGenerator(uint8_t frameType, GeneratorIDType generatorID, FrameGeneratorPtr &frameGenerator);
  
  
  
  virtual ~CameraSystem();
};

}

#endif // VOXEL_CAMERASYSTEM_H
