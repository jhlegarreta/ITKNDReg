/*=========================================================================
 *
 *  Copyright NumFOCUS
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         https://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "itkMetamorphosisImageRegistrationMethodv4.h"
#include "itkImageFileWriter.h"
#include "itkTestingMacros.h"


int itkMetamorphosisImageRegistrationMethodv4Test( int argc, char * argv[] )
{
  if( argc < 2 )
    {
    std::cerr << "Missing parameters." << std::endl;
    std::cerr << "Usage: " << argv[0];
    std::cerr << " outputImage";
    std::cerr << std::endl;
    return EXIT_FAILURE;
    }


  const char * outputImageFileName  = argv[1];

  const unsigned int Dimension = 2;
  using PixelType = float;
  using ImageType = itk::Image< PixelType, Dimension >;

  using MetamorphosisImageRegistrationMethodv4Type = itk::MetamorphosisImageRegistrationMethodv4< ImageType, ImageType >;
  MetamorphosisImageRegistrationMethodv4Type::Pointer metamorphosisImageRegistration =
    MetamorphosisImageRegistrationMethodv4Type::New();

  EXERCISE_BASIC_OBJECT_METHODS( metamorphosisImageRegistration, MetamorphosisImageRegistrationMethodv4,
    TimeVaryingVelocityFieldImageRegistrationMethodv4 );


  std::cout << "Test finished." << std::endl;
  return EXIT_SUCCESS;
}
