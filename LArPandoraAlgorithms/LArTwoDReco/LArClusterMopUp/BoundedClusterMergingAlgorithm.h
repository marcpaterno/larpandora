/**
 *  @file   LArContent/include/LArTwoDReco/LArClusterMopUp/BoundedClusterMergingAlgorithm.h
 * 
 *  @brief  Header file for the bounded cluster merging algorithm class.
 * 
 *  $Log: $
 */
#ifndef LAR_BOUNDED_CLUSTER_MERGING_ALGORITHM_H
#define LAR_BOUNDED_CLUSTER_MERGING_ALGORITHM_H 1

#include "Pandora/Algorithm.h"

#include "LArObjects/LArTwoDSlidingShowerFitResult.h"

#include "LArTwoDReco/LArClusterMopUp/ClusterMopUpAlgorithm.h"

namespace lar
{

/**
 *  @brief  BoundedClusterMergingAlgorithm class
 */

class BoundedClusterMergingAlgorithm : public ClusterMopUpAlgorithm
{
public:
    /**
     *  @brief  Factory class for instantiating algorithm
     */
    class Factory : public pandora::AlgorithmFactory
    {
    public:
        pandora::Algorithm *CreateAlgorithm() const;
    };

private:
    /**
     *  @brief  XSampling class
     */
    class XSampling
    {
    public:
        /**
         *  @brief  Constructor
         * 
         *  @param  fitResult the sliding fit result
         */
        XSampling(const TwoDSlidingFitResult &fitResult);

        float       m_minX;          ///< The min x value
        float       m_maxX;          ///< The max x value
        float       m_xPitch;        ///< The x sampling pitch to be used
    };

    void ClusterMopUp(const pandora::ClusterList &pfoClusters, const pandora::ClusterList &remnantClusters, const ClusterToListNameMap &clusterToListNameMap) const;

    /**
     *  @brief  Get the shower position map containing high and low edge z positions in bins of x
     * 
     *  @param  fitResult the sliding shower fit result
     *  @param  xSampling the x sampling details
     *  @param  showerPositionMap to receive the shower position map
     */
    void GetShowerPositionMap(const TwoDSlidingShowerFitResult &fitResult, const XSampling &xSampling, ShowerPositionMap &showerPositionMap) const;

    /**
     *  @brief  Get the fraction of hits in a cluster bounded by a specified shower position map
     * 
     *  @param  pCluster address of the cluster
     *  @param  xSampling the x sampling details
     *  @param  showerPositionMap the shower position map
     * 
     *  @return the fraction of bounded hits
     */
    float GetBoundedFraction(const pandora::Cluster *const pCluster, const XSampling &xSampling, const ShowerPositionMap &showerPositionMap) const;

    pandora::StatusCode ReadSettings(const pandora::TiXmlHandle xmlHandle);

    unsigned int            m_slidingFitWindow;             ///< The layer window for the sliding linear fits
    float                   m_minBoundedFraction;           ///< The minimum cluster bounded fraction for merging
};

//------------------------------------------------------------------------------------------------------------------------------------------

inline pandora::Algorithm *BoundedClusterMergingAlgorithm::Factory::CreateAlgorithm() const
{
    return new BoundedClusterMergingAlgorithm();
}

} // namespace lar

#endif // #ifndef LAR_BOUNDED_CLUSTER_MERGING_ALGORITHM_H