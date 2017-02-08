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

        // Redirect to setup ONLY IF
        // NO login user in db
        // AND we are NOT on 'setup'
        // AND we are NOT requesting 'register' ON 'post'
        if (!count($users) && !($request -> is('setup')) && !($request -> is('register')) && !($request -> isMethod('post')))
        {
            return redirect('/setup');
        } else {
            //return redirect('/');
        }

        return $next($request);
    }
}
