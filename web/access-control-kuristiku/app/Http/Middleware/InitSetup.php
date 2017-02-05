<?php

namespace KAC\Http\Middleware;

use Closure;
use Illuminate\Support\Facades\DB;

class InitSetup
{
    /**
     * Handle an incoming request.
     *
     * @param  \Illuminate\Http\Request  $request
     * @param  \Closure  $next
     * @return mixed
     */
    public function handle($request, Closure $next)
    {
        $users = DB::table('users')
        -> select('name', 'email')
        -> get();

        if (count($users) || $request -> is('setup')) {
            return $next($request);
        }

        return redirect('setup');
    }
}
