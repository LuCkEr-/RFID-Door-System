<?php

namespace App\Http\Middleware;

use Closure;
use Illuminate\Support\Facades\DB;

class Setup
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

        if (!count($users) && !($request -> is('setup')) && !($request -> is('register')) && !($request -> isMethod('post')))
        {
            return redirect('/setup');
        }

        return $next($request);
    }
}
