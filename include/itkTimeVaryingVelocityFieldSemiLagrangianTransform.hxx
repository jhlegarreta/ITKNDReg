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
#ifndef itkTimeVaryingVelocityFieldSemiLagrangianTransform_hxx
#define itkTimeVaryingVelocityFieldSemiLagrangianTransform_hxx

#include "itkTimeVaryingVelocityFieldSemiLagrangianTransform.h"
#include "itkTimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter.h"

namespace itk
{


template<typename TParametersValueType, unsigned int NDimensions>
TimeVaryingVelocityFieldSemiLagrangianTransform<TParametersValueType, NDimensions>
::TimeVaryingVelocityFieldSemiLagrangianTransform()
{
  m_UseInverse = true;
}


template<typename TParametersValueType, unsigned int NDimensions>
void
TimeVaryingVelocityFieldSemiLagrangianTransform<TParametersValueType, NDimensions>
::IntegrateVelocityField()
{
  if( this->GetVelocityField() )
  {
    using IntegratorType = TimeVaryingVelocityFieldSemiLagrangianIntegrationImageFilter
      <VelocityFieldType, DisplacementFieldType>;

    typename IntegratorType::Pointer integrator = IntegratorType::New();
    integrator->SetInput( this->GetVelocityField() );
    integrator->SetLowerTimeBound( this->GetLowerTimeBound() );
    integrator->SetUpperTimeBound( this->GetUpperTimeBound() );

    if( this->GetVelocityFieldInterpolator() )
      {
      integrator->SetVelocityFieldInterpolator( this->GetModifiableVelocityFieldInterpolator() );
      }

    integrator->SetNumberOfIntegrationSteps( this->GetNumberOfIntegrationSteps() );
    integrator->Update();

    typename DisplacementFieldType::Pointer displacementField = integrator->GetOutput();
    displacementField->DisconnectPipeline();

    this->SetDisplacementField( displacementField );
    this->GetModifiableInterpolator()->SetInputImage( displacementField );

    if(m_UseInverse)
    {
      typename IntegratorType::Pointer inverseIntegrator = IntegratorType::New();
      inverseIntegrator->SetInput( this->GetVelocityField() );
      inverseIntegrator->SetLowerTimeBound( this->GetUpperTimeBound() );
      inverseIntegrator->SetUpperTimeBound( this->GetLowerTimeBound() );
      if( !this->GetVelocityFieldInterpolator() )
      {
        inverseIntegrator->SetVelocityFieldInterpolator( this->GetModifiableVelocityFieldInterpolator() );
      }

      inverseIntegrator->SetNumberOfIntegrationSteps( this->GetNumberOfIntegrationSteps() );
      inverseIntegrator->Update();

      typename DisplacementFieldType::Pointer inverseDisplacementField = inverseIntegrator->GetOutput();
      inverseDisplacementField->DisconnectPipeline();

      this->SetInverseDisplacementField( inverseDisplacementField );
    }

  }
  else
  {
    itkExceptionMacro( "The velocity field does not exist." );
  }
}

} // namespace itk

#endif
