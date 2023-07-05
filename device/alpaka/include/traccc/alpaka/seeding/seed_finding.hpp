/** TRACCC library, part of the ACTS project (R&D line)
 *
 * (c) 2021-2023 CERN for the benefit of the ACTS project
 *
 * Mozilla Public License Version 2.0
 */

#pragma once

// Project include(s).
#include "traccc/edm/seed.hpp"
#include "traccc/edm/spacepoint.hpp"
#include "traccc/seeding/detail/seeding_config.hpp"
#include "traccc/seeding/detail/spacepoint_grid.hpp"
#include "traccc/utils/algorithm.hpp"
#include "traccc/utils/memory_resource.hpp"

// VecMem include(s).
#include <vecmem/utils/copy.hpp>

// System include(s).
#include <functional>

namespace traccc::alpaka {

/// Seed finding for alpaka
class seed_finding : public algorithm<seed_collection_types::buffer(
                         const spacepoint_collection_types::const_view&,
                         const sp_grid_const_view&)> {

    public:
    /// Constructor for the alpaka seed finding
    ///
    /// @param config is seed finder configuration parameters
    /// @param filter_config is seed filter configuration parameters
    /// @param sp_grid spacepoint grid
    /// @param mr vecmem memory resource
    /// @param copy The copy object to use for copying data between device
    ///             and host memory blocks
    seed_finding(const seedfinder_config& config,
                 const seedfilter_config& filter_config,
                 const traccc::memory_resource& mr, vecmem::copy& copy);

    /// Callable operator for the seed finding
    ///
    /// @param spacepoints_view     is a view of all spacepoints in the event
    /// @param g2_view              is a view of the spacepoint grid
    /// @return                     a vector buffer of seeds
    ///
    output_type operator()(
        const spacepoint_collection_types::const_view& spacepoints_view,
        const sp_grid_const_view& g2_view) const override;

    private:
    seedfinder_config m_seedfinder_config;
    seedfilter_config m_seedfilter_config;
    traccc::memory_resource m_mr;
    vecmem::copy& m_copy;
};

}  // namespace traccc::alpaka
