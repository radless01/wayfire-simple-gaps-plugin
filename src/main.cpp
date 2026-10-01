#include <algorithm>
#include <memory>

#include <wayfire/geometry.hpp>
#include <wayfire/option-wrapper.hpp>
#include <wayfire/plugin.hpp>
#include <wayfire/signal-definitions.hpp>
#include <wayfire/signal-provider.hpp>
#include <wayfire/toplevel-view.hpp>
#include <wayfire/toplevel.hpp>
#include <wayfire/workarea.hpp>

#include <wayfire/txn/transaction-manager.hpp>


class wayfire_simple_gaps : public wf::plugin_interface_t
{
    wf::option_wrapper_t<int> gap{"simple-gaps/gap"};

    wf::signal::connection_t<wf::txn::new_transaction_signal> on_new_transaction =
        [this] (wf::txn::new_transaction_signal *ev)
    {
        const double g = std::max(0, gap.value());

        if (g <= 0.0)
        {
            return;
        }

        for (const auto& object : ev->tx->get_objects())
        {
            auto toplevel =
                std::dynamic_pointer_cast<wf::toplevel_t>(object);

            if (!toplevel)
            {
                continue;
            }

            /*
             * Only operate on mapped toplevels.
             */
            if (!toplevel->pending().mapped)
            {
                continue;
            }

            auto view = wf::find_view_for_toplevel(toplevel);

            if (!view)
            {
                continue;
            }

            /*
             * Dialogs / child toplevels are not maximized application
             * windows for the purposes of this plugin.
             */
            if (view->parent)
            {
                continue;
            }

            /*
             * Fullscreen is deliberately excluded.
             */
            if (view->pending_fullscreen())
            {
                continue;
            }

            /*
             * Wayfire defines all four tiled edges as the maximized
             * state. Partial tiling is deliberately ignored.
             */
            if (view->pending_tiled_edges() != wf::TILED_EDGES_ALL)
            {
                continue;
            }

            auto output = view->get_output();

            if (!output || !output->workarea)
            {
                continue;
            }

            const wf::geometry_t workarea =
                output->workarea->get_workarea();

            const double width  = workarea.width  - 2.0 * g;
            const double height = workarea.height - 2.0 * g;

            if (width <= 0.0 || height <= 0.0)
            {
                continue;
            }

            /*
             * This is the important part:
             *
             * desired_size from view_tile_request_signal is only a hint.
             * The transaction's pending geometry is what Wayfire will
             * actually commit.
             */
            toplevel->pending().geometry = {
                workarea.x + g,
                workarea.y + g,
                width,
                height
            };
        }
    };

public:
    void init() override
    {
        wf::get_core().tx_manager->connect(&on_new_transaction);
    }

    void fini() override
    {
        on_new_transaction.disconnect();
    }
};


DECLARE_WAYFIRE_PLUGIN(wayfire_simple_gaps);

